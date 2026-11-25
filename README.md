# About

ESPHome firmware for the LocalBytes Plug32. Switch anything on and off and see what it's using, from Home Assistant or the plug's own web page. It all runs locally. No cloud, no subscription.

## Manual Addition

You can use the following YAML to add the plug to your ESPHome setup.
Please note this does not enable [API Encryption](https://esphome.io/components/api#configuration-variables) or an [OTA Password](https://esphome.io/components/ota.html#configuration-variables).

```yaml
substitutions:
  name: localbytes-plug32-<NAME>
  friendly_name: LocalBytes Plug32 <NAME>

packages:
  localbytes.plug32: github://LocalBytes/esphome-localbytes-plug32/localbytes-plug32.yaml@main

esphome:
  name: ${name}
  name_add_mac_suffix: false
  friendly_name: ${friendly_name}

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
```

# Installation

Connect to the hotspot the plug creates (`LocalBytes Plug32`) and enter your Wi-Fi details, or set up Wi-Fi over Bluetooth from Home Assistant. Once it's on your network, use the "dashboard import" feature of ESPHome to take ownership of the plug.

# Calibration

The Plug32 doesn't need calibrating. If it reads consistently high or low against a meter you trust, adjust **Voltage Divider** (default 2.0) or **Current Resistor** (default 1.0 mΩ) from Home Assistant or the plug's web page.

## Licence

This project is currently published with no specific licence:
- It is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY
- As an individual, you are free to learn from it and use it in your own projects
- You must not claim it as your own

Unless otherwise stated, all code is &copy; Allport-IT LTD. All rights reserved.  
"LocalBytes" and the LocalBytes Logo are &reg; of Allport-IT LTD.
