UE4Plugin_WebApi
==================================

It is a plugin to use the Web API (HTTP communication) for UE4.

[日本語README](/README.jp.md "README.jp.md")

## Concepts

* Wrapping HTTP module
* Class defined in the API unit
* Support OnStart, OnProgress, OnSuccessed, OnFailed, OnCompleted
* PreFilter and PostFilter defined in the API unit

## What is PreFilter and PostFilter ?

PreFilter and PostFilter is processing in communication before and after.  
This has become a generic making, such as can be used in a variety of Web API.

### What you can do in PreFilter

* Change communication method (GET, POST, PUT)
* Add or Remove request parameter
* Change request body format (ex. JSON, MessagePack, ...)

### What you can do in PostFilter

* Change response code.
* Change response body format (ex. JSON, MessagePack, ...)
* Writing your own parsing process for response

## Example movie

![ExampleMovie.gif](/Examples/ExampleMovie.gif)

## Feature examples

### SimpleGet

It is a simple GET communication example.  
[detail...](/Examples/01_SimpleGet/README.md "README.md")

### SimplePost

It is a simple POST communication example.  
[detail...](/Examples/02_SimplePost/README.md "README.md")

### JsonResponse

It is a JSON response parsing example.  
[detail...](/Examples/03_JsonResponse/README.md "README.md")
