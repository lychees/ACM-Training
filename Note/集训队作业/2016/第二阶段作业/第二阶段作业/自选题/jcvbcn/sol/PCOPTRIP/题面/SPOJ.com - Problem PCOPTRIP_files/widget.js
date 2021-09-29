
function __spoj_g_cid(){
	return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
	    var r = Math.random()*16|0, v = c == 'x' ? r : (r&0x3|0x8);
	    return v.toString(16);
	});
}

function __spoj_setCookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires="+d.toUTCString();
    document.cookie = cname + "=" + cvalue + "; " + expires + "; path=/";
}

function __spoj_getCookie(cname) {
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i=0; i<ca.length; i++){
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1);
        if (c.indexOf(name) == 0) return c.substring(name.length, c.length);
    }
    return "";
}

(function() {
	var __spoj_cid = __spoj_getCookie('_sj');
	if(!__spoj_cid){
		__spoj_cid = __spoj_g_cid();
		__spoj_setCookie('_sj', __spoj_cid, 356*2);
	}
	
	var __spoj_uid = '';
	var __spoj_title = encodeURI(document.title);
	var __spoj_hostname = encodeURI(document.location.host);
	var __spoj_pathname = encodeURI(document.location.pathname);
	
	var img = document.createElement("img");
	img.src = 'https://www.google-analytics.com/collect?v=1&tid=UA-10507872-20&cid=' + __spoj_cid + '&uid=' + __spoj_uid + '&t=event&ec=jobs&ea=widget-view&el=CN&ev=1&dp=' + __spoj_pathname + '&dh=' + __spoj_hostname;
	document.body.appendChild(img);
	
})();



(function() {
	var get_list = function(){
		var data = '<ul>';
		
					data = data + '<li><a href="//www.spoj.com/jobs/it-service-specialist" target="_blank"><div class="title">IT Service Specialist</div><div class="location">Shanghai</div></a></li>';
		
		
		data = data + '</ul>';
		
		return data;
	}
	var get_header = function(){
		return '<div class="header"><strong>Spoj jobs</strong><br/>Your skills deserve a suitable job!</div>';
	}
	var get_footer = function(){
		return '<div class="footer">powered by <a href="http://www.spoj.com/jobs" target="_blank">jobs.spoj.com</a></div>';
	}
	var get_style = function(){
		return "<style>\
			.sjw_1{\
				max-width: 400px; width: 100%; border: 1px solid #ddd; border-radius: 4px; box-shadow: 0 1px 1px rgba(0,0,0,.05); \
				font-family: \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif; margin-bottom: 15px; \
			}\
			.sjw_1 a{ text-decoration: none !important; } \
			.sjw_1 ul { padding: 5px; margin: 0px; }\
			.sjw_1 > .header { padding: 10px; background: #333; color: white; border-top-left-radius: 4px; border-top-right-radius: 4px; text-align: center;}\
			.sjw_1 > .footer { font-size: 0.8em; text-align: center; padding: 5px;}\
			.sjw_1 > .footer > a { color: #222; }\
			.sjw_1 > .footer > a:hover { color: #111; }\
			.sjw_1 ul li { list-style: none; cursor: pointer; margin-bottom: 5px; line-height: 15px; color: #333; padding: 5px; }\
			.sjw_1 ul li:hover { background: #eee; } \
			.sjw_1 ul li a .title { font-weight: bold; color: #333;  } \
			.sjw_1 ul li a .location { color: #666;  } \
			.sjw_1 ul li a:hover .title { color: #111;  } \
			</style>";
	}
	document.write('<div class="sjw_1">' + get_header() + get_list() + get_footer() + '</div>' + get_style() );
})();
