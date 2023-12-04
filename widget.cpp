/*
Copyright (C) 2011 Georgia Institute of Technology, University of Utah, Weill
Cornell Medical College

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QTimer>

#include "widget.hpp"

mimic_signal::Plugin::Plugin(Event::Manager* ev_manager)
    : Widgets::Plugin(ev_manager, std::string(mimic_signal::MODULE_NAME))
{
}

mimic_signal::Panel::Panel(QMainWindow* main_window, Event::Manager* ev_manager)
    : Widgets::Panel(
        std::string(mimic_signal::MODULE_NAME), main_window, ev_manager)
{
  setWhatsThis(
      "<p><b>Mimic:</b><br>This module outputs the signal that is used as "
      "input with an optional gain and offset applied..</p>");
  createGUI(get_default_vars(), {});

  QTimer::singleShot(0, this, SLOT(resizeMe()));
}

mimic_signal::Component::Component(Widgets::Plugin* hplugin)
    : Widgets::Component(hplugin,
                         std::string(mimic_signal::MODULE_NAME),
                         mimic_signal::get_default_channels(),
                         mimic_signal::get_default_vars())
    , gain(1.0)
    , offset(0.0)
{
}

void mimic_signal::Component::execute()
{
  // This is the real-time function that will be called
  switch (this->getState()) {
    case RT::State::EXEC:
      writeoutput(0, readinput(0) * gain + offset);
      break;
    case RT::State::INIT:
      setValue(PARAMETER::GAIN, 1.0);
      gain = 1.0;
      setValue(PARAMETER::OFFSET, 0.0);
      offset = 0.0;
      setState(RT::State::EXEC);
      break;
    case RT::State::MODIFY:
      gain = getValue<double>(PARAMETER::GAIN);
      offset = getValue<double>(PARAMETER::OFFSET);
      setState(RT::State::EXEC);
      break;
    case RT::State::PERIOD:
    case RT::State::PAUSE:
      break;
    case RT::State::UNPAUSE:
      setState(RT::State::EXEC);
      break;
    default:
      break;
  }
}

///////// DO NOT MODIFY BELOW //////////
// The exception is if your plugin is not going to need real-time functionality.
// For this case just replace the craeteRTXIComponent return type to nullptr.
// RTXI will automatically handle that case and won't attach a component to the
// real time thread for your plugin.

std::unique_ptr<Widgets::Plugin> createRTXIPlugin(Event::Manager* ev_manager)
{
  return std::make_unique<mimic_signal::Plugin>(ev_manager);
}

Widgets::Panel* createRTXIPanel(QMainWindow* main_window,
                                Event::Manager* ev_manager)
{
  return new mimic_signal::Panel(main_window, ev_manager);
}

std::unique_ptr<Widgets::Component> createRTXIComponent(
    Widgets::Plugin* host_plugin)
{
  return std::make_unique<mimic_signal::Component>(host_plugin);
}

Widgets::FactoryMethods fact;

extern "C"
{
Widgets::FactoryMethods* getFactories()
{
  fact.createPanel = &createRTXIPanel;
  fact.createComponent = &createRTXIComponent;
  fact.createPlugin = &createRTXIPlugin;
  return &fact;
}
}

//////////// END //////////////////////
