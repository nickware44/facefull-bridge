<p align="center">
  <img width="600" height="200" src="https://nickware.group/repository/products/ff/logo.png">
</p>

[facefull official page](https://nickware.group/products/facefull)

Facefull bridge library

Facefull bridge is a communication system which connects application native backend (C++/Java/etc...) and Facefull user interface (runs through webview component). 
This library allows you to use Facefull to create a user interface for native desktop applications using the webview component. In native mode you can use built-in event system to communicate with your native desktop application C++ backend.

This library contains Facefull bridge interface and bridge implementation for wxWidgets (webview/webkit) and Qt5 (webkit) frameworks.
You can use predefined implementations or create your own.

----------------------------------------------------------------
### LICENCE
Facefull bridge library is distributed under the MIT Licence.

----------------------------------------------------------------
### USAGE EXAMPLES
#### 1. [Bridge for wxWidgets](examples/wxwidgets)

Supported OS:
- Windows (uses [Microsoft Edge WebView2 Runtime](https://developer.microsoft.com/en-us/microsoft-edge/webview2?form=MA13LH&cs=578062562))
- Linux (uses WebKit)

#### 2. [Bridge for Qt5](examples/qt5webkit)

Supported OS:
- Linux (uses WebKit)

----------------------------------------------------------------
