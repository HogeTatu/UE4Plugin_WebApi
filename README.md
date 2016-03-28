UE4Plugin_WebApi
==================================

It is a plugin to use the Web API (HTTP communication) for UE4.

[日本語README](/README.jp.md "README.jp.md")

## Concepts

* Wrapping HTTP module
* Class defined in the API unit
* Support OnStart, OnProgress, OnSuccessed, OnFailed, OnCompleted
* Multiple PreFilter and PostFilter processing
* Support OAuth

## What is PreFilter and PostFilter ?

PreFilter and PostFilter is processing in communication before and after.  
This has become a generic making that can be used in a variety of Web API.

### What you can do in PreFilter

* Change communication method (GET, POST, PUT)
* Add or Remove request parameter
* Add or Remove request header (ex. OAuth, ...)
* Change request body format (ex. JSON, MessagePack, ...)

### What you can do in PostFilter

* Change response code.
* Change response body format (ex. JSON, MessagePack, ...)
* Writing your own parsing process for response

## Getting Started

After clone repository or download ZIP, and Place the WebApi directory to the plugin directory of the project.

```
[ProjectName]/Plugins/WebApi
```

After build in VisualStudio, and enable plugin from the configuration of the plugin.

```
Project -> Networking -> WebApi
```

## Example project

WebApiDemo is a example project.  
Start WebApiDemo.uproject, please check the example operations and implementation.  

## Example movie

### Feature Example

[![](http://img.youtube.com/vi/M_3IbU8-NQI/0.jpg)](https://www.youtube.com/watch?v=M_3IbU8-NQI)

### Twitter Example

[![](http://img.youtube.com/vi/Q-mZpALSDRQ/0.jpg)](https://www.youtube.com/watch?v=Q-mZpALSDRQ)

## License

[MIT](/LICENSE "LICENSE")

## Contact

[@HogeTatu](https://twitter.com/HogeTatu)
