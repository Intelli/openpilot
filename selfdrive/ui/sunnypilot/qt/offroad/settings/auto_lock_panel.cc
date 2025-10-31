#include "selfdrive/ui/sunnypilot/qt/offroad/settings/auto_lock_panel.h"

#include <QVBoxLayout>

namespace {
const QStringList kAutoLockRegions = {"US", "CA", "EU", "CN", "AU"};

const QString kAutoLockUsernameParam = "AutoLockUsername";
const QString kAutoLockPasswordParam = "AutoLockPassword";
const QString kAutoLockPinParam = "AutoLockPin";
const QString kAutoLockRegionParam = "AutoLockRegion";

QString maskedValue(const QString &value) {
  return value.isEmpty() ? QObject::tr("Not Set") : QString(value.size(), QChar(0x2022));
}

QString plainValue(const QString &value) {
  return value.isEmpty() ? QObject::tr("Not Set") : value;
}
}  // namespace

AutoLockPanel::AutoLockPanel(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(50, 20, 50, 20);

  list_widget = new ListWidgetSP(this, false);
  list_widget->setSpacing(25);

  addCredentialRow(tr("Username"), kAutoLockUsernameParam, false);
  addCredentialRow(tr("Password"), kAutoLockPasswordParam, true);
  addCredentialRow(tr("PIN"), kAutoLockPinParam, true);
  addRegionRow();

  ScrollViewSP *scroller = new ScrollViewSP(list_widget, this);
  main_layout->addWidget(scroller);

  refreshValues();
}

void AutoLockPanel::addCredentialRow(const QString &title, const QString &param, bool secret) {
  const QString desc = tr("Tap to update. Stored locally in device Params.");
  auto control = new ButtonControlSP(title, tr("EDIT"), desc, this);
  control->showDescription();
  credential_controls.insert(param, control);
  secret_params.insert(param, secret);
  list_widget->addItem(control);

  QObject::connect(control, &ButtonControlSP::clicked, this, [=]() {
    const QString current_value = QString::fromStdString(params.get(param.toStdString()));
    const QString prompt = tr("Enter %1").arg(title.toLower());
    const QString subtitle = tr("Leave blank to clear");
    QString value = InputDialog::getText(prompt, this, subtitle, secret, -1, current_value);
    if (!value.isNull()) {
      const std::string key = param.toStdString();
      if (value.isEmpty()) {
        params.remove(key);
      } else {
        params.put(key, value.toStdString());
      }
      refreshValues();
    }
  });
}

void AutoLockPanel::addRegionRow() {
  const QString desc = tr("Select the Kia/Hyundai account region for remote commands.");
  region_button = new ButtonControlSP(tr("Region"), tr("SELECT"), desc, this);
  region_button->showDescription();
  list_widget->addItem(region_button);

  QObject::connect(region_button, &ButtonControlSP::clicked, this, [=]() {
    const QString current = QString::fromStdString(params.get(kAutoLockRegionParam.toStdString()));
    QString selection = MultiOptionDialog::getSelection(tr("Select Region"), kAutoLockRegions, current, this);
    if (!selection.isEmpty()) {
      params.put(kAutoLockRegionParam.toStdString(), selection.toStdString());
      refreshValues();
    }
  });
}

void AutoLockPanel::refreshValues() {
  for (auto it = credential_controls.constBegin(); it != credential_controls.constEnd(); ++it) {
    const QString param = it.key();
    ButtonControlSP *control = it.value();
    const QString stored = QString::fromStdString(params.get(param.toStdString()));
    const bool secret = secret_params.value(param, false);
    control->setValue(secret ? maskedValue(stored) : plainValue(stored));
  }

  if (region_button) {
    QString region = QString::fromStdString(params.get(kAutoLockRegionParam.toStdString()));
    if (region.isEmpty()) {
      region = tr("Not Set");
    }
    region_button->setValue(region);
  }
}

void AutoLockPanel::showEvent(QShowEvent *event) {
  QWidget::showEvent(event);
  refreshValues();
}