#include "app.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/WBootstrapTheme.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WLeafletMap.h>
#include <Wt/WServer.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>

App::App (const Wt::WEnvironment &env)
    : Wt::WApplication (env), session_ ("unienet")
{
  this->setTitle ("unienet");

  this->root ()->addStyleClass ("container");
  this->setTheme (std::make_shared<Wt::WBootstrapTheme> ());
  this->useStyleSheet ("style.css");

  session_.login ().changed ().connect (this, &App::authEvent);

  std::unique_ptr<Wt::Auth::AuthWidget> authWidget
      = std::make_unique<Wt::Auth::AuthWidget> (
          Session::auth (), session_.users (), session_.login ());

  authWidget->model ()->addPasswordAuth (&Session::passwordService ());
  authWidget->model ()->addOAuth (Session::oAuth ());
  authWidget->setRegistrationEnabled (true);

  authWidget->processEnvironment ();

  this->root ()->addWidget (std::move (authWidget));
}

void
App::authEvent ()
{
  if (session_.login ().loggedIn ())
    {
      const Wt::Auth::User &u = session_.login ().user ();
      log ("notice") << "User " << u.id () << " ("
                     << u.identity (Wt::Auth::Identity::LoginName) << ")"
                     << " logged in.";
      this->createMainView ();
    }
  else
    {
      log ("notice") << "User logged out.";
    }
}

void
App::createMainView ()
{
  auto layout = std::make_unique<Wt::WHBoxLayout> ();
  auto map = std::make_unique<Wt::WLeafletMap> ();
  //  map->setWidth (400);
  //  map->setHeight (400);
  Wt::Json::Object options;
  options["maxZoom"] = 20;
  options["attribution"] = "&copy; <a "
                           "href=\"https://www.openstreetmap.org/"
                           "copyright\">OpenStreetMap</a> contributors";
  map->addTileLayer ("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png",
                     options);
  map->panTo ({ 55.7930907, 49.1143051 });
  layout->addWidget (std::move (map));
  this->root ()->setLayout (std::move (layout));
  //  this->root ()->addWidget (std::move (map));
}

std::unique_ptr<Wt::WApplication>
createApplication (const Wt::WEnvironment &env)
{
  return std::make_unique<App> (env);
}

int
main (int argc, char **argv)
{
  try
    {
      Wt::WServer server{ argc, argv, WTHTTP_CONFIGURATION };

      server.addEntryPoint (Wt::EntryPointType::Application,
                            createApplication);

      Session::configureAuth ();

      server.run ();
    }
  catch (Wt::WServer::Exception &e)
    {
      std::cerr << e.what () << std::endl;
    }
  catch (Wt::Dbo::Exception &e)
    {
      std::cerr << "Dbo exception: " << e.what () << std::endl;
    }
  catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what () << std::endl;
    }
}

// int
// main (int argc, char **argv)
//{
//  return Wt::WRun (argc, argv, [] (const
//  Wt::WEnvironment &env) {
//    return std::make_unique<App> (env);
//  });
//}
