#ifndef APP_H
#define APP_H

#include <Wt/WApplication.h>

#include "session.h"

class App : public Wt::WApplication
{
public:
  App (const Wt::WEnvironment &env);

private:
  Session session_;

  void authEvent ();
  void createMainView ();
};

#endif // APP_H
