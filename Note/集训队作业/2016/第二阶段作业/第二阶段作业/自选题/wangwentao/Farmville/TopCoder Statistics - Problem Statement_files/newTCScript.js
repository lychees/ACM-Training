// JavaScript Document

/*!
 * jQuery Cookie Plugin v1.4.1
 * https://github.com/carhartl/jquery-cookie
 *
 * Copyright 2006, 2014 Klaus Hartl
 * Released under the MIT license
 */
(function (factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD (Register as an anonymous module)
		define(['jquery'], factory);
	} else if (typeof exports === 'object') {
		// Node/CommonJS
		module.exports = factory(require('jquery'));
	} else {
		// Browser globals
		factory(jQuery);
	}
}(function ($) {

	var pluses = /\+/g;

	function encode(s) {
		return config.raw ? s : encodeURIComponent(s);
	}

	function decode(s) {
		return config.raw ? s : decodeURIComponent(s);
	}

	function stringifyCookieValue(value) {
		return encode(config.json ? JSON.stringify(value) : String(value));
	}

	function parseCookieValue(s) {
		if (s.indexOf('"') === 0) {
			// This is a quoted cookie as according to RFC2068, unescape...
			s = s.slice(1, -1).replace(/\\"/g, '"').replace(/\\\\/g, '\\');
		}

		try {
			// Replace server-side written pluses with spaces.
			// If we can't decode the cookie, ignore it, it's unusable.
			// If we can't parse the cookie, ignore it, it's unusable.
			s = decodeURIComponent(s.replace(pluses, ' '));
			return config.json ? JSON.parse(s) : s;
		} catch(e) {}
	}

	function read(s, converter) {
		var value = config.raw ? s : parseCookieValue(s);
		return $.isFunction(converter) ? converter(value) : value;
	}

	var config = $.cookie = function (key, value, options) {

		// Write

		if (arguments.length > 1 && !$.isFunction(value)) {
			options = $.extend({}, config.defaults, options);

			if (typeof options.expires === 'number') {
				var days = options.expires, t = options.expires = new Date();
				t.setMilliseconds(t.getMilliseconds() + days * 864e+5);
			}

			return (document.cookie = [
				encode(key), '=', stringifyCookieValue(value),
				options.expires ? '; expires=' + options.expires.toUTCString() : '', // use expires attribute, max-age is not supported by IE
				options.path    ? '; path=' + options.path : '',
				options.domain  ? '; domain=' + options.domain : '',
				options.secure  ? '; secure' : ''
			].join(''));
		}

		// Read

		var result = key ? undefined : {},
			// To prevent the for loop in the first place assign an empty array
			// in case there are no cookies at all. Also prevents odd result when
			// calling $.cookie().
			cookies = document.cookie ? document.cookie.split('; ') : [],
			i = 0,
			l = cookies.length;

		for (; i < l; i++) {
			var parts = cookies[i].split('='),
				name = decode(parts.shift()),
				cookie = parts.join('=');

			if (key === name) {
				// If second argument (value) is a function it's a converter...
				result = read(cookie, value);
				break;
			}

			// Prevent storing a cookie that we couldn't decode.
			if (!key && (cookie = read(cookie)) !== undefined) {
				result[name] = cookie;
			}
		}

		return result;
	};

	config.defaults = {};

	$.removeCookie = function (key, options) {
		// Must not alter options, thus extending a fresh object...
		$.cookie(key, '', $.extend({}, options, { expires: -1 }));
		return !$.cookie(key);
	};

}));

var MINIMUM_PAYMENT_ACCRUAL_AMOUNT;
var PAY_ME_CONFIRMATION_TEMPLATE;
var USER_PAYMENT_METHOD;

var ev = 'click';
if ($.support.touch) {
	ev = 'tap'
}
var app = {
	init : function() {
		app.setPlaceholder($('.connected .email'));
	},
	setPlaceholder : function(selector) {
		$(selector).each(function() {
			_this = $(this);
			var text = _this.attr('placeholder');
			_this.val(text).addClass('isBlured');
			_this.on('focus', function() {
				$(this).on('blur', function() {
					$(this).unbind('blur', arguments.callee);
					if ($.trim($(this).val()) === '') {
						$(this).val(text).addClass("isBlured");
					}
				});
				if ($(this).val() === text) {
					$(this).val('').removeClass("isBlured");
				}
			});
		});
	}
}

/** methods ported from tcscript.js **/

document.write('<link type="image/x-icon" rel="shortcut icon" href="/i/favicon.ico"/>');

function getGraph(url,wd,ht) {
    var last=0;
    var daHt = parseInt(ht) + parseInt('49');
    var size = "top=2,left=2,width="+wd+",height="+daHt+"status=0,resizable=yes";
    popup = window.open('/statistics/graphPopup.jsp?'+url+'&width='+wd+'&height='+ht,null,size);
    return;
}

function getGraph(url,wd,ht,name) {
    var last=0;
    var daHt = parseInt(ht) + parseInt('49');
    var size = "top=2,left=2,width="+wd+",height="+daHt+",status=0,resizable=yes";
    popup = window.open('/statistics/graphPopup.jsp?'+url+'&width='+wd+'&height='+ht,name,size);
    return;
}

function tcTime() {
    w=window.open("http://www.topcoder.com/tc?module=Static&d1=calendar&d2=time","Time","top=2,left=2,width=250,height=50,resizable=yes,status=1");
    return;
}

function sponsorLink(spons) {
    w=window.open(spons,"Sponsor");
    return;
}

function sponsorLinkWindow(spons,nam,top,lef,wid,hei) {
    w=window.open(spons,nam,"top="+top+",left="+lef+",width="+wid+",height="+hei+",resizable=yes,toolbar=no,location=no,scrollbars=no,menubar=no,status=no");
    return;
}

function openWin(url, name, w, h) {
    var left = Math.round((screen.availWidth - w)/2);
    var top = Math.round((screen.availHeight-h)/2);
    win = window.open(url, name, "scrollbars=yes,toolbar=no,resizable=yes,menubar=no"
        + ",width=" + w + ",height=" + h
        + ",left=" + left + ",top=" + top);
    win.location.href = url;
    win.focus();
}

function infoWindow(url) {
    var width = 300
    var height = 250
    var left = (screen.availWidth - width) / 2;
    var top = (screen.availHeight-height)/2;
    OpenWin=this.open(url,"Info",
        "toolbar=no,menubar=no,location=no,scrollbars=yes,resizable=yes"
            + ",width=" + width + ",height=" + height
            + ",left=" + left + ",top=" + top);
}

function openProblemRating(id) {
    var width = Math.round(560);
    var height = Math.round(660);
    var left = Math.round((screen.availWidth - width) / 2);
    var top = 0;
    var cmd = "toolbar=no,menubar=no,location=no,scrollbars=yes,resizable=yes,top="+top+",left="+left+",width=" + width + ",height=" + height + ",status=0";
    var name="problemRating";
    window.open('/tc?module=ProblemRatingQuestions&pid='+id,name,cmd);
    return;
}


function goTo(selection) {
    sel = selection.options[selection.selectedIndex].value;
    if (sel == "alltimewin")
    {
        window.location = "/stat?c=all_time_wins";
    }
    else if (sel == "winningdebuts")
    {
        window.location = "/stat?c=winning_debuts";
    }
    else if (sel == "impressivedebuts")
    {
        window.location = "/stat?c=impressive_debuts";
    }
    else if (sel == "hightesttotal")
    {
        window.location = "/stat?c=highest_totals";
    }
    else if (sel == "ratingpointgain")
    {
        window.location = "/stat?c=biggest_rating_gains";
    }
    else if (sel == "consecwins")
    {
        window.location = "/stat?c=most_consecutive_wins";
    }
    else if (sel == "submissionaccuracy")
    {
        window.location = "/stat?c=highest_accuracy";
    }
    else if (sel == "challengesuccess")
    {
        window.location = "/stat?c=best_challengers";
    }


    else {}
}


function doWrite(s) {
    document.write(s);
}

/**
 * Validates the pagination parameters.
 *
 * @return {Boolean} true if pagination parameters are valid; false otherwise.
 */
function checkPaymentHistoryForm() {
    var myForm = document.f;
    var nr = myForm.nr.value;
    var sr = myForm.sr.value;

    var error = '';
    if (!isPositiveNumber(nr)) {
        error += 'Number of records is not positive numeric value';
        error += '\n';
    }
    if (!isPositiveNumber(sr)) {
        error += 'Starting record number is not positive numeric value';
        error += '\n';
    }

    if (error != '') {
        alert(error);
        return false;
    } else {
        $('input[name=paymentId]').attr('disabled', 'disabled');
        return true;
    }

}

/**
 * Checks if specified text provides positive integer number.
 *
 * @param v a number to validate.
 * @return {Boolean} true if specified string provided positive integer number: false otherwise.
 */
function isPositiveNumber(v) {
    var regExp = new RegExp('^[0-9]+$');
    var matches = regExp.test(v);
    if (matches) {
        var n = parseInt(v);
        if (n <= 0) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

function tcTime() {
    w=window.open("http://www.topcoder.com/tc?module=Static&d1=calendar&d2=time","Time","top=2,left=2,width=250,height=50,resizable=yes,status=1");
    return;
}


// Popup show function
function showPopup(id) {
    var popup = $('#' + id),
        wrapper = popup.closest('.popup-wrapper');
    popup.show();
    wrapper.show();
}

// Popup hide function
function hidePopup(elem) {
    var popup = $(elem).closest('.popup'),
        wrapper = popup.closest('.popup-wrapper');
    popup.hide();
    wrapper.hide();
}

/**
 * Close modal windows
 */
function closeModal() {
    $("#modal-background, #new-modal-window .outLay").hide();
}

/**
 * Adjust the overlay background and model window and display them
 */
function adjustAndShow(modal) {
    $("#modal-background").css("height", document.body.scrollHeight > document.body.offsetHeight ? (document.body.scrollHeight>$(window).height()? document.body.scrollHeight :$(window).height()) : (document.body.offsetHeight>$(window).height()? document.body.offsetHeight:$(window).height()));
    $("#modal-background, " + modal).show();
    $("#new-modal-window").css("margin-left", - $("#new-modal-window").width() / 2 + "px").css("margin-top", - $("#new-modal-window").height() / 2 + "px");
    var height = 0;
    $(modal + ".outLay .modalBody .modalContent li").each(function(){
        height += $(this).height();
    });
    if(!$(modal+ ".outLay .modalBody .modalContent").hasClass("multiple")){
        $(modal+ ".outLay .modalBody .modalContent li:first").css("padding-top", ($(".outLay .modalBody .modalContent").height() - height) / 2 + "px");
    }
    if (jQuery.browser.msie && jQuery.browser.version == '9.0') {
        $(modal + " .modalBody").css("margin-top", "-2px");
    }
}


/**
 * Updates the text of Pay Me button with total amount of selected payments.
 */
function updatePayMe() {
    var total = calcTotalPayment();
    if (total >= 0) {
        $('#payMe').val('Pay Me: $' + total.toFixed(2));
    } else {
        $('#payMe').val('Pay Me: -$' + Math.abs(total.toFixed(2)));
    }
    if (total < MINIMUM_PAYMENT_ACCRUAL_AMOUNT || !isUserPaymentMethodValid()) {
        $('#payMe').attr('disabled', 'disabled');
    } else {
        $('#payMe').removeAttr('disabled');
    }
}

/**
 * Calculates the total amount of payments selected by user.
 *
 * @return {Number} a total amount of selected payments.
 */
function calcTotalPayment() {
    var total = 0.00;
    $('.payable:checked').each(function () {
        var amount = parseFloat($(this).parent().find('.paymentNetAmount').val());
        total += amount;
    });
    return total;
}

/**
 * Checks if current user has a payment method set to any value other than NULL or 1,3,4 (Not Set,Wire,ACH)
 */
function isUserPaymentMethodValid() {
    return (USER_PAYMENT_METHOD != null) && (USER_PAYMENT_METHOD != 1) && (USER_PAYMENT_METHOD != 3) && (USER_PAYMENT_METHOD != 4);
}

function showError(/*String*/ message, /*Object*/ dom){
    $(dom).after('<span class="bigRed">'+ message +'</span>');
}

/**
 * Validate the input field to update or create a second email.
 */
function validateAddSecondEmail( /*Object*/ inputControl){
    $('.bigRed').remove();

    var EMAIL_REGEX_CHECKER = new RegExp(".+@[^\\.]+(\\.[^\\.]+)*");

    if( !nonEmptyValidate($(inputControl).val()) ){
        showError("Please enter the email to continue.", inputControl);
        return false;
    }

    if( ! EMAIL_REGEX_CHECKER.test( $(inputControl).val() ) ){
        showError("The email has a bad format.", inputControl);
        return false;
    }

    return true;
}

/**
 * Validate the find user input field.
 */
function validateFindUserField(/*Object*/ inputControl){

    $('.bigRed').remove();

    if( !nonEmptyValidate($(inputControl).val()) ){
        showError("Please input something to search.", inputControl);
        return false;
    }

    return true;
}
/**
 * Validate the email type radio, which is to select the password recovery email account.
 */
function validateEmailTypeRadio(/*Object*/ emailTypeRadioTable){
    $('.emailTypeRadioMessage', emailTypeRadioTable).remove();
    var selected = $('input[type="radio"]:checked',emailTypeRadioTable);
    if( selected.length == 0 ){
        showEmailTypeRadioError( emailTypeRadioTable, "Please select one email to continue." );
        return false;
    }

    return true;
}

/**
 * This code is used in recoverByEmail.jsp to show error message when the email type is not selected correctly.
 */
function showEmailTypeRadioError(/*Object*/ emailTypeRadioTable, /*String*/ message ){
    $('tbody', emailTypeRadioTable).prepend('<tr class="emailTypeRadioMessage"><td colspan="2"><span class="bigRed">'+ message +'</span></td></tr>');
}

/*
 * Do not-empty validation.
 */
function nonEmptyValidate(/*String*/ query){
    return $.trim(query).length != 0;
}
/**
 * Check the password's length is between [ min, max ].
 */
function checkPasswordLength(/*String*/ password, /*int*/ min, /*int*/ max){
    return password.length >= min && password.length <= max;
}
/**
 * Check the input password contains only valid chars, which is defined in passwordAlphabet.
 */
function basicPasswordValidate(/*String*/ password, /*String*/ passwordAlphabet){
    for(var i = 0; i < password.length; i++){
        var appear = false;
        for(var j = 0; j < passwordAlphabet.length; j++){
            if(password.charAt(i) == passwordAlphabet.charAt(j)){
                appear = true;
            }
        }
        if(!appear)return false;
    }
    return true;
}

function adjustFooterMargin() {

    var height_diff = $( window ).height() - $( 'body' ).height();
    if ( height_diff > 0 ) {
        $( '.bottom-footer' ).css( 'margin-top', height_diff );
    } else {
        $( '.bottom-footer' ).css( 'margin-top', "" );
    }
}

function doLogOutTC() {
     var temp = window.location.hostname.split('.').reverse();
     var root_domain = '.' + temp[1] + '.' + temp[0];
	 $.removeCookie("tcjwt", {domain:root_domain});
	 $.removeCookie("tcsso", {domain:root_domain});
	 window.location.replace("https://www" + root_domain);
}

$(document).ready(function() {

    $(".leftNavWrapper").parent().hide();

    adjustFooterMargin();

    $("tr[valign=top]").addClass('alignTop');
    $("tr[valign=bottom]").addClass('alignBottom');

    // setup current node
    if ($("#nodeName").length && $("#nodeName").val()) {
        var currentNode = $('#' + $("#nodeName").val());

        currentNode.css({color: '#FF8A00', 'font-weight': "bold"});

        currentNode.parents("li:eq(1)").addClass('expanded').children().show();
    }


    if( $("div.leftNavWrapper").parent().is("td")) {
        $("section.navigation").parent().css('width', '185px').css('display', 'block');

        $("body > table").addClass('mainContent');

        $("td.bodyText").each(function(index, t) {
            if($(this).closest('table')[0] === $("table:eq(0)")[0]){
                $(this).nextAll().remove();
            };
        });

        $("td.bodyColumn").each(function(index, t) {
            if($(this).closest('table')[0] === $("table:eq(0)")[0]){
                $(this).nextAll().remove();
            };
        });

        $("td.statTableSpacer").each(function(index, t) {
            if($(this).closest('table')[0] === $("table:eq(0)")[0]){
                $(this).nextAll().remove();
            };
        });

    }

   $("table").css('visibility', 'visible');

	// main Nav
	$('#mainNav').on(ev, function(){
		$('.sidebarNav').css('opacity', 1);
		$('.content, #navigation').toggleClass('moving');
		window.setTimeout(function(){$('body').toggleClass('stop-scrolling');},1);
	});
	$('#mainNav .root').on(ev, function(e){
		e.stopPropagation();
	});

	$('#mainNav .root > li').mouseenter(function(){
		$('.child',$(this)).stop().slideDown('fast');
	});
	$('#mainNav .root > li').mouseleave(function(){
		$('.child',$(this)).stop().slideUp('fast');
	});

	//Left Navigation
	$('.navigation li a').on(ev, function(){
		if($(this).siblings('ul').length && $(this).parents('li').hasClass('expanded')){
			$(this).parents('li').removeClass('expanded');
			$(this).siblings('ul').slideUp();
		}else{
			$(this).parents('li').addClass('expanded');
			$(this).siblings('ul').slideDown();
		}
	});

	//Tab
	$('.top-brand .actions').on(ev, 'a',function(){
		var idx = $(this).index($('.top-brand .actions a'));
		$('.top-brand .actions a').removeClass('active');
		$(this).addClass('active');
		$('.brand-container table').hide();
		$('.brand-container table').eq(idx).show();
	});

	//Chrome Hack
	if(navigator.userAgent.toLowerCase().match(/chrome/) != null) {
		$('#footer .twFollowIcon').css({
			'margin-left': '1px'
		});
	}

	app.init();

    // Popup close handler
    $('.popup-wrapper')
        .on(ev, '.close-popup', function () {
            hidePopup(this);
        })
        .on(ev, '.overlay', function () {
            var wrapper = $(this).closest('.popup-wrapper');
            wrapper.hide();
            $('.popup', wrapper).hide();
        });


    // payment page
    $('.uncheckAll').click(function() {
        $('.uncheckable').attr('checked', false);
        updatePayMe();
    });

    $('.checkAll').click(function () {
        $('.checkable').attr('checked', true);
        updatePayMe();
    });

    $('.payable').click(function() {
        if (!$(this).hasClass('negative')) {
            updatePayMe();
        }
    });

    $('#payMe').click(function() {
        if (isUserPaymentMethodValid()) {
            var total = calcTotalPayment();
            var confirmationMessage = PAY_ME_CONFIRMATION_TEMPLATE.replace('{0}', '$' + total.toFixed(2));

            if (confirm(confirmationMessage)) {
                var myForm = document.f;
                myForm.method = 'POST';
                myForm.module.value = 'PayMe';
                myForm.submit();
            }
        }
    });

    $('.getable').click(function () {
        var myForm = document.f;
        myForm.method = 'GET';
        myForm.module.value = 'PaymentHistory';

        $('input[name=paymentId]').attr('disabled', 'disabled');
    });

    updatePayMe();

    $('.buttonArea .register').click(function(){
        // the 'isAnonymous' is defined in the projectDetails.jsp file
        if(!isAnonymous) {
            var thisObj = this;
            adjustAndShow("#preloaderModal");
            //Check Project Permission using ajax call
            $.ajax({
                type: "get",
                url: '?module=CheckPermission',
                success: function(data){
                    var result = $.parseJSON(data);
                    closeModal();
                    if('OK' !== result.msg && !result.isAnonymous) {
                        adjustAndShow("#errorModal");
                    } else {
                        location.href = $(thisObj).attr('href');
                    }
                }
            });
            return false;
        } else {
            // for the Anonymous user, go to the viewRegistration page directly.
            return true;
        }
    });

    $("#new-modal-window .closeModal, #new-modal-window .defaultBtn").click(function(){
        closeModal();
    });

    $("#m_cs_competitions").parent().find("a:eq(0)").css("color", "#f8941e");

    if ($(".post-container").length > 0) {

        var count = 0;

        try {

        // load the news
        $.get("https://www.topcoder.com/blog", function (data) {

            $(".post-container").html($(data + '').find(".grid-2-3").html());
            $(".post-container .pagingWrapper").remove();


             $(data + '').find("#replacercode div.post").each(function () {

                 if(count > 5) {
                     return false;
                 }

                 var title = $(this).find(".title a:eq(1)").text();
                 var category = $(this).find(".title a:eq(0) span").text();
                 var categoryLink = $(this).find(".title a:eq(0)").attr('href');
                 var imgLink = $(this).find("div.entry img").attr('src');
                 var imgLinkHref = $(this).find("div.entry img").parent().attr('href');
                 $(this).find("div.entry img").remove();
                 var entryContent = $(this).find("div.entry").html();
                 var date = $(this).find(".byline").text();
                 date = date.replace('Posted on', '');
                 date = $.trim(date.replace(/by.*/, ''));
                 var author = $(this).find(".byline span").text();
                 var plink = $(this).find(".links a:eq(0)").attr('href');

                 var templateHTML = $(".post-container").find(".postTemplate").html();
                 var postItem = $('' + templateHTML);
                 postItem.find("a.title").text(title).attr('href', plink);
                 postItem.find("div.date span").text(date);
                 postItem.find("div.author span").text(author);
                 postItem.find("div.category a").text(category).attr('href', categoryLink);
                 if(imgLink) {
                     postItem.find("a.figure img").attr('src', imgLink).attr('alt', '');
                     if(imgLinkHref) {
                         postItem.find("a.figure").attr('href', imgLinkHref);
                     }
                 } else {
                     postItem.find("a.figure").remove();
                 }

                 postItem.find(".details").prepend(entryContent + '');
                 postItem.find(".details .more a").attr('href', plink);

                 $(".post-container").append($("<section class='post'></section>").html(postItem));
                 count ++;
             })

            adjustFooterMargin();
        });

        } catch(e) {
            // ignore

        }
    }

    if($(".recentBlogPosts").length > 0) {

        try {

        jQuery.getFeed({
            url: '/feed/?post_type=blog',
            success: function(feed) {
                $.each(feed.items, function(index, item){

                    if(index > 2) {
                        return;
                    }

                    var itemHTML = $("#blogTemplate").html();
                    var blogEntry = $('' + itemHTML);
                    var dateArray = item.updated.split(' ');
                    blogEntry.find('a:eq(0)').attr('href', item.link).text(dateArray[2] + ' ' + dateArray[1]);
                    blogEntry.append(item.description).find("br").remove();

                    blogEntry.insertBefore('#blogTemplate');
                })
            }
        });

        } catch(e) {
            // ignore
        }
    }


    // forEach method to be used to iterate arrays and NodeList
    function forEach(array, callback, scope) {
        var i;

        for (i = 0; i < array.length; i += 1) {
            callback.call(scope, i, array[i]);
        }
    }


    // Helper function for toggling class of an element
    // modified from: http://youmightnotneedjquery.com/#toggle_class
    function toggleClass(el, className, toggle) {
        if (el.classList) {
            if (typeof(toggle) !== 'boolean') {
                el.classList.toggle(className);
            } else if (toggle) {
                el.classList.add(className);
            } else {
                el.classList.remove(className);
            }
        } else {
            var classes = el.className.split(' ');
            var existingIndex = classes.indexOf(className);

            if (typeof(toggle) !== 'boolean') {
                toggle = existingIndex >= 0;
            }

            if (toggle) {
                if (existingIndex >= 0) {
                    classes.splice(existingIndex, 1);
                }
            } else {
                if (existingIndex === -1) {
                    classes.push(className);
                }
            }

            el.className = classes.join(' ');
        }
    }


    // Elements and variables
    var body = document.getElementsByTagName('body')[0],
        searchBox = document.getElementById('searchBox'),
        searchNeedle = searchBox ? searchBox.value : null,
        suggestionList = document.querySelectorAll('.suggestion-list')[0],
        headerWrapper = document.querySelectorAll('.header-wrapper')[0],
        userMenu = document.querySelectorAll('.user-menu')[0],
        suggestionSamples = null,
        counter = 0,
        suggestionsHtml = '';

    // Attach click handler to menu buttons
    forEach(document.querySelectorAll('.btn-open-menu, .btn-close-menu'), function (i, el) {
        el.addEventListener('click', function () {
            toggleClass(body, 'menu-visible');
        });
    });

    // Attach click handler to login button(s)
    forEach(document.querySelectorAll('.btn-login, .btn-logout'), function (i, el) {
        el.addEventListener('click', function () {
            toggleClass(body, 'menu-visible', false);
            toggleClass(headerWrapper, 'user-authenticated');
            toggleClass(userMenu, 'anonymous-menu');
        });
    });


});
