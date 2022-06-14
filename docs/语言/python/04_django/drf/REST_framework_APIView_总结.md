
### APIView
```python
from rest_framework.views import APIView


def dispatch(self, request, *args, **kwargs):
    """
    `.dispatch()` is pretty much the same as Django's regular dispatch,
    but with extra hooks for startup, finalize, and exception handling.
    """
    self.args = args
    self.kwargs = kwargs
    request = self.initialize_request(request, *args, **kwargs)  # 初始化request对象，改为rest_framework提供的Request对象
    self.request = request
    self.headers = self.default_response_headers  # deprecate?

    try:
        self.initial(request, *args, **kwargs)

        # Get the appropriate handler method
        if request.method.lower() in self.http_method_names:
            handler = getattr(self, request.method.lower(),
                              self.http_method_not_allowed)
        else:
            handler = self.http_method_not_allowed

        response = handler(request, *args, **kwargs)

    except Exception as exc:
        response = self.handle_exception(exc)

    self.response = self.finalize_response(request, response, *args, **kwargs)
    return self.response
```
### 视图 method : initialize_request() 
```python
def initialize_request(self, request, *args, **kwargs):
    """
    Returns the initial request object.
    """
    parser_context = self.get_parser_context(request)

    return Request(
        request,  # 原始的djangorequest
        parsers=self.get_parsers(),  # 解析器验证
        authenticators=self.get_authenticators(),  # 用户权限验证
        negotiator=self.get_content_negotiator(),  # 节流
        parser_context=parser_context
    )
```

### APIView method: get_parsers()
```python
def get_parsers(self):
    """
    Instantiates and returns the list of parsers that this view can use.
    """
    return [parser() for parser in self.parser_classes]
```
取得视图中定义的parser_classes列表，使用列表推导式依次获取解析器对象。

用户权限验证类，节流类也是一样的方式。

### initial()
封装好request后来进行一系列的验证，APIView.dispatch->self.initial(request, *args, **kwargs)
```python
def initial(self, request, *args, **kwargs):
    """
    Runs anything that needs to occur prior to calling the method handler.
    """
    self.format_kwarg = self.get_format_suffix(**kwargs)

    # Perform content negotiation and store the accepted info on the request
    neg = self.perform_content_negotiation(request)
    request.accepted_renderer, request.accepted_media_type = neg

    # Determine the API version, if versioning is in use.
    version, scheme = self.determine_version(request, *args, **kwargs)
    request.version, request.versioning_scheme = version, scheme

    # Ensure that the incoming request is permitted
    self.perform_authentication(request)  # 用户认证  
    self.check_permissions(request)  # 检查权限
    self.check_throttles(request)  # 节流
```
### perform_authentication(request)
```python
def perform_authentication(self, request):
    """
    Perform authentication on the incoming request.

    Note that if you override this and simply 'pass', then authentication
    will instead be performed lazily, the first time either
    `request.user` or `request.auth` is accessed.
    """
    request.user

@property
def user(self):
    """
    Returns the user associated with the current request, as authenticated
    by the authentication classes provided to the request.
    """
    if not hasattr(self, '_user'):
        with wrap_attributeerrors():
            self._authenticate()
    return self._user

def _authenticate(self):
    """
    Attempt to authenticate the request using each authentication instance
    in turn.
    """
    for authenticator in self.authenticators:
        try:
            user_auth_tuple = authenticator.authenticate(self)
        except exceptions.APIException:
            self._not_authenticated()
            raise

        if user_auth_tuple is not None:
            self._authenticator = authenticator
            self.user, self.auth = user_auth_tuple
            return

    self._not_authenticated()
```