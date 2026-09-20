"""EV9 OP-long main engagement and knob actions, latched from press through release."""
from opendbc.car import ButtonType, structs
from opendbc.car.hyundai.values import CAR


class EV9CruiseButtons:
  def __init__(self):
    self._pressed: dict[int, int] = {}
    self._blocked: set[int] = set()
    self._main_pressed = False
    self._knob_pressed: set[int] = set()

  def update(self, CP, CS, *, enabled: bool | None, cruise_initialized: bool) -> None:
    if CP.carFingerprint != CAR.KIA_EV9 or not CP.openpilotLongitudinalControl or CP.pcmCruise:
      self._pressed.clear()
      self._blocked.clear()
      self._main_pressed = False
      self._knob_pressed.clear()
      return

    # An unknown software state cannot authorize a new knob-press engagement.
    # Still emit the matching release so cruise-speed button timers can clear.
    if enabled is None:
      self._blocked.update(self._pressed)
    if self._pressed.get(ButtonType.cancel) == ButtonType.decelCruise and self._engagement_interrupted(CS):
      self._blocked.add(ButtonType.cancel)

    events = []
    button_enable = False
    knob_buttons = (ButtonType.accelCruise, ButtonType.decelCruise, ButtonType.cancel)
    main_conflict = bool(self._knob_pressed) or any(b.type in knob_buttons for b in CS.buttonEvents)
    main_pressed = any(b.type == ButtonType.mainCruise and b.pressed for b in CS.buttonEvents)
    knob_transition = (any(b.pressed and b.type in knob_buttons for b in CS.buttonEvents) and
                       any(not b.pressed and b.type in knob_buttons for b in CS.buttonEvents))
    for button in CS.buttonEvents:
      original = button.type.raw
      mapped = original
      blocked = False
      if original == ButtonType.mainCruise:
        main_on_press = button.pressed and not self._main_pressed
        self._main_pressed = button.pressed
        # CarState has already toggled main availability. Keep the physical event
        # for AOL, and request engagement only on this accepted ON press.
        main_ready = (CS.cruiseState.available and CS.canValid and not CS.canTimeout and not CS.steeringDisengage and
                      not ((CS.brakePressed or CS.regenBraking) and not CS.standstill))
        button_enable |= main_on_press and enabled is False and not main_conflict and main_ready
      if original in knob_buttons:
        if button.pressed:
          self._knob_pressed.add(original)
        else:
          self._knob_pressed.discard(original)
      if original in (ButtonType.accelCruise, ButtonType.cancel):
        if button.pressed:
          if original not in self._pressed:
            if enabled is False and (original == ButtonType.cancel or not cruise_initialized):
              mapped = ButtonType.decelCruise
            self._pressed[original] = mapped
            if original == ButtonType.cancel and (knob_transition or main_pressed):
              self._blocked.add(original)
          mapped = self._pressed[original]
          if original == ButtonType.cancel and mapped == ButtonType.decelCruise and self._engagement_interrupted(CS):
            self._blocked.add(original)
        else:
          mapped = self._pressed.pop(original, original)
          blocked = original in self._blocked or (original == ButtonType.cancel and knob_transition)
          self._blocked.discard(original)

      events.append(structs.CarState.ButtonEvent(type=mapped, pressed=button.pressed))
      if not button.pressed and mapped in (ButtonType.accelCruise, ButtonType.decelCruise):
        button_enable |= not blocked and (mapped == original or enabled is not None)

    CS.buttonEvents = events
    # CarInterface computed this from the physical events before normalization.
    CS.buttonEnable = button_enable

  @staticmethod
  def _engagement_interrupted(CS) -> bool:
    return (not CS.cruiseState.available or not CS.canValid or CS.canTimeout or CS.brakePressed or CS.gasPressed or
            CS.regenBraking or CS.steeringDisengage)
