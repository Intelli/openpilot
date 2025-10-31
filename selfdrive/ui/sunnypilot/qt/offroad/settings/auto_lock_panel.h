#pragma once

#include <QMap>
#include <QStringList>
#include <QShowEvent>

#include "selfdrive/ui/sunnypilot/qt/offroad/settings/settings.h"
#include "selfdrive/ui/sunnypilot/qt/widgets/controls.h"
#include "selfdrive/ui/sunnypilot/qt/widgets/scrollview.h"
#include "selfdrive/ui/qt/widgets/input.h"

class AutoLockPanel : public QWidget {
  Q_OBJECT

public:
  explicit AutoLockPanel(QWidget *parent = nullptr);

private:
  void addCredentialRow(const QString &title, const QString &param, bool secret = false);
  void addRegionRow();
  void refreshValues();
  void showEvent(QShowEvent *event) override;

  Params params;
  ListWidgetSP *list_widget = nullptr;
  QMap<QString, ButtonControlSP*> credential_controls;
  ButtonControlSP *region_button = nullptr;
  QMap<QString, bool> secret_params;
};