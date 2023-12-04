
#include <string>

#include <rtxi/widgets.hpp>

// This is an generated header file. You may change the namespace, but
// make sure to do the same in implementation (.cpp) file
namespace mimic_signal
{

constexpr std::string_view MODULE_NAME = "mimic-signal";

enum PARAMETER : Widgets::Variable::Id
{
  // set parameter ids here
  GAIN = 0,
  OFFSET,
};

inline std::vector<Widgets::Variable::Info> get_default_vars()
{
  return {{PARAMETER::GAIN,
           "Gain",
           "Scaling of the copied signal",
           Widgets::Variable::DOUBLE_PARAMETER,
           1.0},
          {PARAMETER::OFFSET,
           "Offset",
           "Offset of the copied signal",
           Widgets::Variable::DOUBLE_PARAMETER,
           0.0}};
}

inline std::vector<IO::channel_t> get_default_channels()
{
  return {
      {
          "Vin",
          "The signal to be mimicked",
          IO::INPUT,
      },
      {
          "Vout",
          "The scaled and offset copy of the input",
          IO::OUTPUT,
      },
  };
}

class Panel : public Widgets::Panel
{
  Q_OBJECT
public:
  Panel(QMainWindow* main_window, Event::Manager* ev_manager);

  // Any functions and data related to the GUI are to be placed here
};

class Component : public Widgets::Component
{
public:
  explicit Component(Widgets::Plugin* hplugin);
  void execute() override;

private:
  double gain;
  double offset;
  // Additional functionality needed for RealTime computation is to be placed
  // here
};

class Plugin : public Widgets::Plugin
{
public:
  explicit Plugin(Event::Manager* ev_manager);
};

}  // namespace mimic_signal
