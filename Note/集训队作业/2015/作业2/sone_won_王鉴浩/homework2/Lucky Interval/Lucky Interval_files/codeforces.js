function info(message) {
    if (console) {
        console.log("INFO: " + message);
    }
}

function debug(message) {
    if (console) {
        console.log("DEBUG: " + message);
    }
}

function error(message) {
    if (console) {
        console.error("DEBUG: " + message);
    }
    window.alert("ERROR: " + message);
}

$.fn.hasAttr = function (name) {
    var attr = $(this).attr(name);
    return typeof attr !== 'undefined' && attr !== false;
};

Codeforces = new function () {
    //noinspection JSUnusedGlobalSymbols
    this.ping = function (pingUrl) {
        Codeforces.setCookie("lastOnlineTimeUpdaterInvocation", new Date().getTime());
        $.post(pingUrl, {ftaa: window._ftaa, bfaa: window._bfaa}, function (result) {
            var div = document.createElement("div");

            for (var i = 0; i < result.length; ++i) {
                //noinspection InnerHTMLJS
                div.innerHTML = result[i].text;
                var text = div.innerText || div.textContent || div.text;

                if (false && Notification) { // Just remove "false && " to enable desktop notifications.
                    if (Notification.permission === "default") {
                        Notification.requestPermission();
                    }

                    if (Notification.permission === "granted") {
                        //noinspection ObjectAllocationIgnored
                        new Notification(result[i].name, {
                            body: text,
                            icon: "../favicon.png"
                        });
                    } else {
                        alert(result[i].name + "\n----------\n\n" + text);
                    }
                } else {
                    alert(result[i].name + "\n----------\n\n" + text);
                }
            }
        }, "json");
    };

    this.parseSeconds = function (seconds) {
        var ap = 0;
        if (seconds.length == 9) {
            ap = seconds.charAt(0) - '0';
            seconds = seconds.substring(1);
        }
        if (seconds.length == 8 && seconds.charAt(2) == ':' && seconds.charAt(5) == ':') {
            var s = (seconds.charAt(7) - '0') + 10 * (seconds.charAt(6) - '0');
            var m = (seconds.charAt(4) - '0') + 10 * (seconds.charAt(3) - '0');
            var h = (seconds.charAt(1) - '0') + 10 * (seconds.charAt(0) - '0') + 100 * ap;
            return s + 60 * m + 60 * 60 * h;
        } else {
            return 0;
        }
    };

    this.formatSS = function (seconds) {
        if (seconds <= 9) {
            return "0" + seconds;
        } else {
            return seconds;
        }
    };

    this.formatSeconds = function (seconds) {
        var s = seconds % 60;
        seconds = (seconds - s) / 60;
        var m = seconds % 60;
        var h = (seconds - m) / 60;
        return Codeforces.formatSS(h) + ":" + Codeforces.formatSS(m) + ":" + Codeforces.formatSS(s);
    };

    this.countdown = function () {
        var now = new Date().getTime();
        var countdownElements = $(".countdown");
        var starts = [];

        var index = 0;
        countdownElements.each(function () {
            ++index;
            $(this).attr("cdid", "i" + index);
        });

        var callback = function () {
            countdownElements.each(function () {
                var countdownElement = $(this);
                var textBeforeRedirect = countdownElement.attr("textBeforeRedirect");
                var redirectUrl = countdownElement.attr("redirectUrl");
                var home = countdownElement.attr("home");
                var noRedirection = countdownElement.attr("noRedirection");
                var hideOnCountdownFinish = countdownElement.attr("hideOnCountdownFinish");
                var showAnotherOnCountdownFinish = countdownElement.attr("showAnotherOnCountdownFinish");
                var showAnotherClass = countdownElement.attr("showAnotherClass");
                var hideAnotherOnCountdownFinish = countdownElement.attr("hideAnotherOnCountdownFinish");
                var hideAnotherClass = countdownElement.attr("hideAnotherClass");

                var id = countdownElement.attr("cdid");
                var txt = countdownElement.text();
                var s = Codeforces.parseSeconds(txt);
                if (s > 0) {
                    if (starts[id] == undefined) {
                        starts[id] = s;
                    }
                    var passed = Math.floor((new Date().getTime() - now) / 1000);
                    var val = starts[id] - passed;
                    if (val >= 0) {
                        countdownElement.text(Codeforces.formatSeconds(val));
                    }
                    if (val <= 0) {
                        if (hideOnCountdownFinish == "true" || hideOnCountdownFinish == "yes"
                            || hideOnCountdownFinish == "y" || hideOnCountdownFinish == "1") {
                            countdownElement.hide();
                        }

                        if (showAnotherOnCountdownFinish == "true" || showAnotherOnCountdownFinish == "yes"
                            || showAnotherOnCountdownFinish == "y" || showAnotherOnCountdownFinish == "1") {
                            $("." + showAnotherClass).show();
                        }

                        if (hideAnotherOnCountdownFinish == "true" || hideAnotherOnCountdownFinish == "yes"
                            || hideAnotherOnCountdownFinish == "y" || hideAnotherOnCountdownFinish == "1") {
                            $("." + hideAnotherClass).hide();
                        }

                        if (noRedirection != "true" && noRedirection != "yes"
                            && noRedirection != "y" && noRedirection != "1") {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect, function () {
                                    if (redirectUrl) {
                                        window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 2000));
                                    } else {
                                        window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 2000));
                                    }
                                });
                            } else {
                                if (redirectUrl) {
                                    window.setTimeout(Codeforces.redirect(redirectUrl), Math.floor(Math.random() * 5000));
                                } else {
                                    window.setTimeout(Codeforces.reload, Math.floor(Math.random() * 5000));
                                }
                            }
                        } else {
                            if (textBeforeRedirect) {
                                Codeforces.alert(textBeforeRedirect);
                            }
                        }
                    }
                }
            });
            window.setTimeout(callback, 1000);
        };
        window.setTimeout(callback, 0);
    };

    this.facebox = function (target, home) {
        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        var clone = $(target).clone();
        $.facebox.reveal(clone.show(), null);

        CodeforcesIframe.updatePopups();
    };

    this.alert = function (messageHtml, okHandler, okText) {
        Codeforces.confirm(messageHtml, okHandler, null, okText, null);
    };

    this.confirm = function (messageHtml, okHandler, cancelHandler, okText, cancelText) {
        var dialogHtml = "<div class='confirm-proto'><div class='text'>&nbsp;<\/div><div><hr\/><div style='text-align:center;'><input class='ok' name='codeforces-dialog-ok-button' type='button' value='%OK%'\/><input class='cancel' name='codeforces-dialog-cancel-button' type='button' value='%Cancel%'\/><\/div><\/div><\/div>"
            .replace("%OK%", okText ? okText : "OK")
            .replace("%Cancel%", cancelText ? cancelText : "Cancel");
        var p = $(dialogHtml).css('display', 'none');
        $(".text", p).html(messageHtml);

        var defaultButtonName = null;

        var cancelButton = $(".cancel", p);
        if (cancelHandler) {
            cancelButton.click(function () {
                $.facebox.close();
                cancelHandler();
            });

            defaultButtonName = cancelButton.attr("name");
        } else {
            cancelButton.css("display", "none");
        }

        var okButton = $(".ok", p);
        if (okHandler) {
            okButton.click(function () {
                $.facebox.close();
                okHandler();
            });

            defaultButtonName = okButton.attr("name");
        } else {
            okButton.css("display", "none");
        }

        if (!okHandler && !cancelHandler) {
            $(".ok", p).parent().parent().css("display", "none");
        }

        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        $.facebox.reveal(p.show(), null);

        CodeforcesIframe.updatePopups();

        if (defaultButtonName) {
            $("input[name=" + defaultButtonName + "]").focus();
        }
    };

    //noinspection JSUnusedGlobalSymbols
    this.confirmWithoutClose = function (messageHtml, okHandler, cancelHandler, okText, cancelText) {
        var dialogHtml = "<div class='confirm-proto'><div class='text'>&nbsp;<\/div><div><hr\/><div style='text-align:center;'><input class='ok' name='codeforces-dialog-ok-button' type='button' value='%OK%'\/><input class='cancel' name='codeforces-dialog-cancel-button' type='button' value='%Cancel%'\/><\/div><\/div><\/div>"
            .replace("%OK%", okText ? okText : "OK")
            .replace("%Cancel%", cancelText ? cancelText : "Cancel");
        var p = $(dialogHtml).css('display', 'none');
        $(".text", p).html(messageHtml);

        var defaultButtonName = null;

        var cancelButton = $(".cancel", p);
        if (cancelHandler) {
            cancelButton.click(function () {
                //$.facebox.close();
                cancelHandler();
            });

            defaultButtonName = cancelButton.attr("name");
        } else {
            cancelButton.css("display", "none");
        }

        var okButton = $(".ok", p);
        if (okHandler) {
            okButton.click(function () {
                //$.facebox.close();
                okHandler();
            });

            defaultButtonName = okButton.attr("name");
        } else {
            okButton.css("display", "none");
        }

        if (!okHandler && !cancelHandler) {
            $(".ok", p).parent().parent().css("display", "none");
        }

        $("facebox").facebox(/*{
         closeImage    : (home != undefined ? home + "/" : "") + 'images/facebox/closelabel.gif',
         splitterImage : (home != undefined ? home + "/" : "") + 'images/facebox/splitter.png'
         }*/);
        $.facebox.loading();
        $.facebox.reveal(p.show(), null);

        CodeforcesIframe.updatePopups();

        if (defaultButtonName) {
            $("input[name=" + defaultButtonName + "]").focus();
        }
    };

    this.showMessage = function (message) {
        $.jGrowl(message, {position: 'bottom-right', life: 10000});
        CodeforcesIframe.updatePopups();
    };

    //noinspection JSUnusedGlobalSymbols
    this.focusOnError = function () {
        var found = false;

        $(".table-form .error").each(function () {
            if (!found) {
                var val = $.trim($(this).text());
                if (val.length > 0) {
                    var classes = this.className.split(" ");
                    for (var i in classes) {
                        if (classes[i].match(/for__.*/)) {
                            var name = classes[i].substring(5);
                            found = true;

                            $(".table-form input[name=" + name + "]").focus();
                            return;
                        }
                    }
                }
            }
        });

        if (!found) {
            var focusInput = null;
            $("input.focus, select.focus, textarea.focus").each(function () {
                if (focusInput === null) {
                    focusInput = $(this);
                }
            });
            $(".table-form input, .table-form select, .table-form textarea").each(function () {
                if (focusInput === null) {
                    var elem = $(this);
                    if (elem.val() === "" && elem.attr("type") != "hidden" && !elem.hasAttr("readonly")) {
                        focusInput = elem;
                    }
                }
            });
            if (focusInput !== null) {
                focusInput.focus();
            }
        }
    };

    this.reload = function () {
        window.location.reload();
    };

    this.redirect = function (link) {
        window.location = link;
    };

    this.clearAjaxFormErrors = function (selector) {
        var form = $(selector);
        form.find("*").each(function () {
            var classes = this.className.split(" ");
            var found = false;
            for (var i in classes) {
                if (classes[i].indexOf("error__") === 0) {
                    found = true;
                }
            }
            if (found) {
                $(this).find(".error").hide();
                $(this).find(".notice").show();
            }
        });
    };

    this.setAjaxFormError = function (selector, key, value) {
        $(selector).find("." + key).each(function () {
            $(".notice", this).hide();
            $(".error", this).html(value).show();
        });
    };

    this.setAjaxFormErrors = function (selector, data) {
        var result = false;
        this.clearAjaxFormErrors(selector);
        for (var i in data) {
            if (i.indexOf("error__") == 0) {
                this.setAjaxFormError(selector, i, data[i]);
                result = true;
            }
        }
        return result;
    };

    //noinspection JSUnusedGlobalSymbols
    this.isEnglishText = function (s) {
        var latinLetterCount = 0;
        for (var i = 0; i < s.length; i++) {
            var c = s.charAt(i);
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
                latinLetterCount++;
            }
        }
        return latinLetterCount > s.length / 2;
    };

    //noinspection JSUnusedGlobalSymbols
    this.replaceDataForRoundTable = function (selector, titles, data, widths) {
        var rt = $(selector);
        var table = $(".rtable", rt);
        table.fadeOut(250, function () {
            var content = "";

            content += "<tr>";
            for (var j = 0; j < titles.length; j++) {
                var attr = "";
                if (j === 0) {
                    attr += " class=\"left\"";
                }
                if (widths != undefined && widths[j] != undefined) {
                    attr += " style=\"width:" + widths[j] + ";\"";
                }
                content += "<th" + attr + ">";
                content += titles[j] + "</th>";
            }
            content += "</tr>";

            for (var i = 0; i < data.length; i++) {
                var row = data[i];
                content += "<tr>";
                for (var j = 0; j < row.length; j++) {
                    var clazz = "";
                    if (j === 0) {
                        clazz += "left ";
                    }
                    if (i + 1 == data.length) {
                        clazz += "bottom ";
                    }
                    if (i % 2 === 0) {
                        clazz += "dark ";
                    }
                    content += "<td class=\"" + clazz + "\">" + row[j] + "</td>";
                }
                content += "</tr>";
            }
            table.html(content);
            table.fadeIn(250);
        });
    };

    /*
     this.changeRowIndex = function(selector, from, to) {
     if (from != to) {
     var init = $(selector + " tr:nth-child(" + from + ")");
     var target = $(selector + " tr:nth-child(" + to + ")");
     var duration = 250 + 50 * Math.abs(from - to);
     if (init != undefined && target != undefined) {
     var tr = init.clone();
     $(selector).append(tr);
     tr.css("display", "block").css("position", "absolute")
     .css("top", init.position().top).css("background", "#FFF7DB !important")
     .css("border", "3px solid #e1e1e1").css("font-size", "1.25em")
     .css("left", (target.position().left-10) + "px");
     tr.find("td").css("background", "#FFF7DB !important");
     tr.show();
     init.animate({
     opacity: "hide"
     }, {
     queue: false,
     duration: duration
     });
     tr.animate({
     "top": target.position().top
     }, duration, function() {
     tr.hide();
     init.detach();
     init.show();
     if (from > to)
     target.before(init);
     else
     target.after(init);
     $(".datatable").each(function() {
     $(this).find("td").removeClass("bottom").removeClass("dark");
     $(this).find("tr:first th").addClass("top");
     $(this).find("tr:last td").addClass("bottom");
     $(this).find("tr:odd td").addClass("dark");
     $(this).find("tr td:first-child, tr th:first-child").addClass("left");
     $(this).find("tr td:last-child, tr th:last-child").addClass("right");
     });
     });
     }
     }
     }
     */

    this.updateDatatables = function () {
        var tds = $(".datatable tr td");
        tds.removeClass("top");
        tds.removeClass("bottom");
        tds.removeClass("dark");
        tds.removeClass("left");
        tds.removeClass("right");
        $(".datatable").each(function () {
            $(this).find("tr:first th").addClass("top");
            $(this).find("tr:last td").addClass("bottom");
            $(this).find("tr:odd td").addClass("dark");
            $(this).find("tr td:first-child, tr th:first-child").addClass("left");
            $(this).find("tr td:last-child, tr th:last-child").addClass("right");
        });
    };

    this.isGym = function (contestId) {
        return contestId >= 100000;
    };

    //noinspection JSUnusedGlobalSymbols
    this.parentForm = function (elem) {
        while (elem && elem.tagName != "FORM") {
            elem = elem.parentNode;
        }
        return elem;
    };

    this.setCookie = function (name, value) {
        document.cookie = name + "=" + escape(value);
    };

    this.getCookie = function (name) {
        var prefix = name + "=";
        var from = document.cookie.indexOf(prefix);
        if (from < 0) {
            return null;
        } else {
            var to = document.cookie.indexOf(";", from + prefix.length);
            if (to < 0) {
                to = document.cookie.length;
            }
            return unescape(document.cookie.substring(from + prefix.length, to));
        }
    };

    var _0xca4e = ["\x6C\x65\x6E\x67\x74\x68", "\x63\x68\x61\x72\x43\x6F\x64\x65\x41\x74", "\x66\x6C\x6F\x6F\x72"];

    function ca76fd64a80cdc35(_0x87ebx2) {
        var _0x87ebx3 = 0;
        for (var _0x87ebx4 = 0; _0x87ebx4 < _0x87ebx2[_0xca4e[0]]; _0x87ebx4++) {
            _0x87ebx3 = (_0x87ebx3 + (_0x87ebx4 + 1) * (_0x87ebx4 + 2) * _0x87ebx2[_0xca4e[1]](_0x87ebx4)) % 1009;
            if (_0x87ebx4 % 3 === 0) {
                _0x87ebx3++;
            }
            if (_0x87ebx4 % 2 === 0) {
                _0x87ebx3 *= 2;
            }
            if (_0x87ebx4 > 0) {
                _0x87ebx3 -= Math[_0xca4e[2]](_0x87ebx2[_0xca4e[1]](Math[_0xca4e[2]](_0x87ebx4 / 2)) / 2) * (_0x87ebx3 % 5);
            }
            while (_0x87ebx3 < 0) {
                _0x87ebx3 += 1009;
            }
            while (_0x87ebx3 >= 1009) {
                _0x87ebx3 -= 1009;
            }
        }
        return _0x87ebx3;
    }

    //noinspection JSUnusedGlobalSymbols
    this.signForms = function () {
        var etc = Codeforces.tta();
        if (etc) {
            $("form:not([method=get])").each(function () {
                var f = $(this);
                var upd = 0;
                f.find("input[name='_tta']").each(function () {
                    ++upd;
                    $(this).val(etc);
                });
                if (upd === 0) {
                    f.append("<input type='hidden' name='_tta' value='" + etc + "'/>");
                }
            });
        }
    };

    this.tta = function () {
        return ca76fd64a80cdc35(Codeforces.getCookie("39ce7"));
    };

    function isNumber(n) {
        return !isNaN(parseFloat(n)) && isFinite(n);
    }

    this.getFromStorage = function (key) {
        return window.localStorage[key];
    };

    this.getFromStorage = function (key, defaultValue) {
        if (!window.localStorage) {
            return defaultValue;
        }

        if (window.localStorage[key] == null || window.localStorage[key] == "null"
            || window.localStorage[key] == NaN || window.localStorage[key] == "NaN"
            || window.localStorage[key] == undefined || window.localStorage[key] == "undefined") {
            window.localStorage[key] = defaultValue;
        }

        var result = window.localStorage[key];

        if (isNumber(result)) {
            return parseFloat(result);
        }

        if (result == "true") {
            return true;
        }

        if (result == "false") {
            return false;
        }

        return result;
    };

    this.putToStorage = function (key, value) {
        if (window.localStorage) {
            window.localStorage[key] = value;
        }
    };

    this.eventBus = null;
    this.eventBusSubscriptions = [];
    this.eventBusReconnectCount = 0;

    this.setupEventBus = function () {
        var that = this;
        if (that.eventBus == null) {
            that.eventBus = new vertx.EventBus("http://pubsub.codeforces.com:85/sub", {protocols_whitelist: ["websocket", "xhr-streaming", "xdr-streaming", "xhr-polling", "xdr-polling", "iframe-htmlfile", "iframe-eventsource", "iframe-xhr-polling"], debug: true});

            that.eventBus.onopen = function () {
                for (var channel in that.eventBusSubscriptions) {
                    if (that.eventBusSubscriptions.hasOwnProperty(channel)) {
                        info("Connected to the channel \"" + channel.substring(0, 4) + "\".");
                        that.eventBus.registerHandler(channel, function (msg) {
                            if (that.eventBusSubscriptions[channel]) {
                                for (var h in that.eventBusSubscriptions[channel]) {
                                    if (that.eventBusSubscriptions[channel].hasOwnProperty(h)) {
                                        that.eventBusSubscriptions[channel][h](msg);
                                    }
                                }
                            }
                        });
                    }
                }
            };

            that.eventBus.onclose = function () {
                that.eventBusReconnectCount++;
                info("Disconnected from the channels [" + that.eventBusReconnectCount + "].");
                that.eventBus = null;
                if (that.eventBusReconnectCount < 10) {
                    that.setupEventBus();
                }
            };
        }
    };

    //noinspection JSUnusedGlobalSymbols
    this.subscribe = function (channel, handler) {
        var that = this;
        that.setupEventBus();

        if (that.eventBusSubscriptions[channel] == undefined) {
            that.eventBusSubscriptions[channel] = [];
        }

        that.eventBusSubscriptions[channel].push(handler);
    };

    //noinspection JSUnusedGlobalSymbols
    this.getGlobalSubmissionsChannel = function () {
        return $("meta[name=\"gc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getContestSubmissionsChannel = function () {
        return $("meta[name=\"cc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getParticipantSubmissionsChannel = function () {
        return $("meta[name=\"pc\"]").attr("content");
    };

    //noinspection JSUnusedGlobalSymbols
    this.getCsrfToken = function () {
        var meta = $("meta[name='X-Csrf-Token']").attr("content");
        if (meta && meta.length == 32) {
            return meta;
        }

        var span = $("span.csrf-token").attr("data-csrf");
        if (span && span.length == 32) {
            return span;
        }

        return undefined;
    };

    this.getDimensionPx = function (wrappedElement, cssPropertyName) {
        var dimension = wrappedElement.css(cssPropertyName);

        if (dimension) {
            var pxIndex = dimension.indexOf("px");
            if (pxIndex > 0) {
                return parseInt(dimension.substr(0, pxIndex))
            }
        }

        return -1;
    };

    this.getWidthPx = function (wrappedElement) {
        var width = this.getDimensionPx(wrappedElement, "width");

        if (width === -1) {
            var clientWidth = wrappedElement.get(0).clientWidth;
            if (clientWidth > 0) {
                width = clientWidth;
            }
        }

        return width;
    };

    this.getHeightPx = function (wrappedElement) {
        var height = this.getDimensionPx(wrappedElement, "height");

        if (height === -1 || true) {
            var clientHeight = wrappedElement.get(0).clientHeight;
            if (clientHeight > 0) {
                height = clientHeight;
            }
        }

        return height;
    };

    this.equalizeElements = function (jquerySelectorOrElements, equalizeWidth, equalizeHeight) {
        if (typeof(equalizeWidth) === 'undefined') {
            equalizeWidth = true;
        }

        if (typeof(equalizeHeight) === 'undefined') {
            equalizeHeight = true;
        }

        var elements = $(jquerySelectorOrElements);
        var maxWidth = 0;
        var maxHeight = 0;

        elements.each(function () {
            if (equalizeWidth) {
                var width = $(this).width();

                var currentWidth = Math.max(
                    width ? width : 0,
                    this.offsetWidth ? this.offsetWidth : 0,
                    (this.clientLeft ? this.clientLeft : 0) + (this.clientWidth ? this.clientWidth : 0)
                );

                if (currentWidth > maxWidth) {
                    maxWidth = currentWidth;
                }
            }

            if (equalizeHeight) {
                var height = $(this).height();

                var currentHeight = Math.max(
                    height ? height : 0,
                    this.offsetHeight ? this.offsetHeight : 0,
                    (this.clientTop ? this.clientTop : 0) + (this.clientHeight ? this.clientHeight : 0)
                );


                if (currentHeight > maxHeight) {
                    maxHeight = currentHeight;
                }
            }
        });

        elements.each(function () {
            if (equalizeWidth) {
                this.style.width = maxWidth + "px";
            }

            if (equalizeHeight) {
                this.style.height = maxHeight + "px";
            }
        });
    };
};

CodeforcesIframe = new function () {
    this.updatePopupDimensions = function () {
        //noinspection JSUnresolvedVariable
        var parentDimensions = window.parentDimensions;
        if (!parentDimensions) {
            return;
        }

        var parentWindow = parentDimensions.window;
        var container = parentDimensions.container;

        $("#facebox").find(".popup .content > div").each(function () {
            var facebox = $(this);

            var width = Codeforces.getWidthPx(facebox);
            if (width !== -1) {
                var maxWidth = Math.max(350, container.offsetWidth - 100);
                if (width > maxWidth) {
                    facebox.css("width", maxWidth + "px");
                }
            }

            var height = Codeforces.getHeightPx(facebox);
            if (height !== -1) {
                var maxHeight = Math.max(250, Math.min(container.offsetHeight - 100, parentWindow.innerHeight - 200));
                if (height > maxHeight) {
                    facebox.css("height", maxHeight + "px");
                }
            }
        });
    };

    this.updatePopupLocations = function () {
        //noinspection JSUnresolvedVariable
        var parentDimensions = window.parentDimensions;
        if (!parentDimensions) {
            return;
        }

        var parentWindow = parentDimensions.window;
        var container = parentDimensions.container;

        /* Offset of the visible area top from the top of IFrame. */
        var top = parentWindow.scrollY - container.offsetTop;
        top = Math.max(top, 0);

        /* Offset of the visible area bottom from the bottom of IFrame. */
        var bottom = container.offsetHeight + container.offsetTop - parentWindow.scrollY - parentWindow.innerHeight;
        bottom = Math.max(bottom, 0);

        $("#jGrowl").each(function () {
            var element = $(this);
            var offset = 0;
            var elementBottom = bottom + offset;
            var elementHeight = Codeforces.getHeightPx(element);

            if (elementHeight !== -1) {
                elementBottom = Math.min(elementBottom, Math.max(offset, window.innerHeight - elementHeight - offset));
            }

            if (elementBottom !== Codeforces.getDimensionPx(element, "bottom")) {
                element.css("bottom", elementBottom + "px");
            }
        });

        $("#facebox").each(function () {
            var element = $(this);
            var offset = 50;
            var elementTop = top + offset;
            var elementHeight = Codeforces.getHeightPx(element);

            if (elementHeight !== -1) {
                elementTop = Math.min(elementTop, Math.max(offset, window.innerHeight - elementHeight - offset));
            }

            if (elementTop !== Codeforces.getDimensionPx(element, "top")) {
                element.css("top", elementTop + "px");
            }

            var elementWidth = Codeforces.getWidthPx(element);
            if (elementWidth !== -1) {
                var elementLeft = Codeforces.getDimensionPx(element, "left");
                if (elementLeft !== -1) {
                    var centeredElementLeft = (container.offsetWidth - elementWidth) / 2;
                    if (elementLeft !== centeredElementLeft) {
                        element.css("left", centeredElementLeft + "px");
                    }
                }
            }
        });
    };

    this.updatePopups = function () {
        this.updatePopupDimensions();
        this.updatePopupLocations();
    };
};
