#ifndef APP_H
#define APP_H

#include <Wt/WApplication.h>

#include "eventdatabase.h"
#include "session.h"

struct Borders;

class App : public Wt::WApplication
{
public:
  App (const Wt::WEnvironment &env);

private:
  Session session_;
  EventDatabase eventDb_;

  void authEvent ();
  void createMainView ();
  Borders getMapBorders (const std::unique_ptr<Wt::WLeafletMap> &map,
                         const std::pair<double, double> coords) const;
};

struct Borders
{
  double up;
  double left;
  double down;
  double right;
};

#endif // APP_H
