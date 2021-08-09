#ifndef MARKERFORMWIDGET_H
#define MARKERFORMWIDGET_H

#include <Wt/WButtonGroup.h>
#include <Wt/WCheckBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDateEdit.h>
#include <Wt/WDoubleSpinBox.h>
#include <Wt/WGroupBox.h>
#include <Wt/WLeafletMap.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WRadioButton.h>
#include <Wt/WSignal.h>
#include <Wt/WSpinBox.h>
#include <Wt/WTextEdit.h>
#include <Wt/WTime.h>
#include <Wt/WTimeEdit.h>

#include "event.h"
#include "eventdatabase.h"

class MarkerFormWidget : public Wt::WContainerWidget
{
public:
  MarkerFormWidget ();
  MarkerFormWidget (Wt::WLeafletMap::Coordinate coords);
  MarkerFormWidget (Event &event);

  Wt::Signal<const Event> saveSignal;

private:
  Wt::WLineEdit *titleEdit_;
  Wt::WDoubleSpinBox *xEdit_;
  Wt::WDoubleSpinBox *yEdit_;
  Wt::WDateEdit *startDateEdit_;
  Wt::WTimeEdit *startTimeEdit_;
  std::unique_ptr<Wt::WCheckBox> endEditCheck_;
  Wt::WDateEdit *endDateEdit_;
  Wt::WTimeEdit *endTimeEdit_;
  enum class ParticipantsLimit
  {
    NO_LIMIT = 0,
    UNKNOWN = 1,
    FIXED = 2 // ??? fixed
  };
  Wt::WButtonGroup *participantLimitButtonGroup_;
  Wt::WSpinBox *participantsLimitEdit_;
  Wt::WTextEdit *descriptionEdit_;
  Wt::WPushButton *saveButton_;

  bool validate () const;
  bool inline validateTitleEdit () const;
  bool inline validateXEdit () const;
  bool inline validateYEdit () const;
  bool inline validateStartDateEdit () const;
  bool inline validateStartTimeEdit () const;
  bool inline validateEndDateEdit () const;
  bool inline validateEndTimeEdit () const;
  bool inline validateParticipantsLimitEdit () const;
  bool inline validateDescriptionEdit () const;
  void emitSave ();
  void showError ();
};

#endif // MARKERFORMWIDGET_H
