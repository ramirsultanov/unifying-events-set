#include "app.h"

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/WBootstrapTheme.h>
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
  auto t = std::make_unique<Wt::WTemplate> ();
  //  t->setTemplateText (
  //      "<!DOCTYPE html>"
  //      "<html>"
  //      "<head>"
  //      "<title>Add Map</title>"

  //      "<style type=${text_css}>"
  //      "#map {"
  //      "height: 400px;"
  //      "width: 100%;"
  //      "}"
  //      "</ style><script>"
  //      "function"
  //      "initMap ()"
  //      "{"
  //      "const uluru = { lat : -25.344, lng : 131.036 };"
  //      "const map = new google.maps.Map (document.getElementById (${map}),
  //      {" "zoom : 4," "center : uluru,"
  //      "});"
  //      "const marker = new google.maps.Marker ({"
  //      "position : uluru,"
  //      "map : map,"
  //      "});"
  //      "}"
  //      "</script>"
  //      "</head>"
  //      "<body>"
  //      "<h3>My Google Maps Demo</h3>"
  //      "<!--The div element for the map -->"
  //      "<div id=${map}></div>"

  //      "<!-- Async script executes immediately and must be after any DOM "
  //      "elements used in callback. -->"
  //      "<script"
  //      "src=${service_url}"
  //      "async"
  //      "></script>"
  //      "</body>"
  //      "</html>");
  //  t->bindString ("text_css", "text/css", Wt::TextFormat::Plain);
  //  t->bindString ("map", "map", Wt::TextFormat::Plain);
  //  t->bindString ("service_url",
  //                 "https://maps.googleapis.com/maps/api/"
  //                 "js?key=AIzaSyAemT9seeS35-y-yMN9TxPRnoBjtxSkti0&callback="
  //                 "initMap&libraries=&v=weekly",
  //                 Wt::TextFormat::Plain);

  //  t->setTemplateText ("<iframe width=${width} height=${height}
  //  style=${style} "
  //                      "loading=${lazy} allowfullscreen
  //                      src=${src}</iframe>");
  //  t->bindString ("width", "600", Wt::TextFormat::XHTML);
  //  t->bindString ("height", "450", Wt::TextFormat::XHTML);
  //  t->bindString ("style", "border: 0", Wt::TextFormat::XHTML);
  //  t->bindString ("loading", "lazy", Wt::TextFormat::XHTML);
  //  t->bindString ("src",
  //                 "https://www.google.com/maps/embed/v1/"
  //                 "view?center=55.7879,49.1233&zoom=10&key=AIzaSyAemT9seeS35-y-"
  //                 "yMN9TxPRnoBjtxSkti0",
  //                 Wt::TextFormat::XHTML);
  //  auto container = std::make_unique<Wt::WContainerWidget> ();
  //  container->addNew<Wt::WText> (Wt::WString (
  //      "<iframe width=\"600\" height=\"450\" style=\"border: 0\" "
  //      "loading=\"lazy\" allowfullscreen "
  //      "src=\"https://www.google.com/maps/embed/v1/"
  //      "view?center=55.7879,49.1233&zoom=10&key=AIzaSyAemT9seeS35-y-"
  //      "yMN9TxPRnoBjtxSkti0\"</iframe>"));
  //  this->root ()->addWidget (std::move (container));
  auto text = std::make_unique<Wt::WText> (
      "<iframe width=\"600\" height=\"450\" style=\"border: 0\" "
      "loading=\"lazy\" allowfullscreen "
      "src=\"https://www.google.com/maps/embed/v1/"
      "view?center=55.7879,49.1233&zoom=10&key=AIzaSyAemT9seeS35-y-"
      "yMN9TxPRnoBjtxSkti0\"</iframe>",
      Wt::TextFormat::UnsafeXHTML);
  this->root ()->addWidget (std::move (text));
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
