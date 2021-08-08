#include "markerformwidget.h"

#include <Wt/WHBoxLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>
#include <Wt/WVBoxLayout.h>

#include <string>

MarkerFormWidget::MarkerFormWidget () : Wt::WContainerWidget ()
{
  auto mainLayout = this->addWidget (std::make_unique<Wt::WVBoxLayout> ());
  auto make_pair_label_and_input = [&mainLayout] (const std::string label,
                                                  const std::string editText
                                                  = "") {
    auto hLayout
        = mainLayout->addLayout (std::make_unique<Wt::WHBoxLayout> ());
    hLayout->addWidget (std::make_unique<Wt::WLabel> (label));
    return hLayout->addWidget (std::make_unique<Wt::WLineEdit> (editText));
  };
  this->titleEdit_ = make_pair_label_and_input ("Title");
}
