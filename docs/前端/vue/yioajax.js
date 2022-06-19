/**
 * Created by yiouejv on 2018/11/12.
 */
// 对jquery的ajax的封装
// 自动添加csrf_token

'use strict';
var yioajax = {
	'get':function(args) {
		args['method'] = 'get';
		this.ajax(args);
	},
	'post':function(args) {
		args['method'] = 'post';
		this.ajax(args);
	},
	'ajax':function(args) {
		// 设置csrftoken
		this._ajaxSetup();
		$.ajax(args);
	},
	'_ajaxSetup': function() {
		$.ajaxSetup({
			'beforeSend':function(xhr,settings) {
				if (!/^(GET|HEAD|OPTIONS|TRACE)$/i.test(settings.type) && !this.crossDomain) {
                    var csrftoken = $('meta[name=csrf_token]').attr('content');
                    xhr.setRequestHeader("X-CSRFToken", csrftoken);

					// django 的csrftoken
					var csrftoken = $('input[name=csrfmiddlewaretoken]').attr('value');
					xhr.setRequestHeader("X-CSRFtoken", csrftoken);
                }
			}
		});
	}
};
