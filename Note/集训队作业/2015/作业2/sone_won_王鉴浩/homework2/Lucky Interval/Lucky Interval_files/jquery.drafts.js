(function ($) {
    var textareasToListen = [];
    var buttonsToListen = [];
    var alertedOnFail = false;
    var consecutiveFailCount = 0;

    var updateButtonsPosition = function () {
        $.each(textareasToListen, function (index, textarea) {
            var button = buttonsToListen[index];
            var buttonContainer = textarea;

            var buttonContainerSelector = button.attr("buttonContainerSelector");
            if (buttonContainerSelector && buttonContainerSelector.length > 0) {
                buttonContainer = $($(buttonContainerSelector)[0]);
            }

            var xOffset = buttonContainer.get(0).clientWidth - button.outerWidth() - 6;
            var yOffset = 8;

            var buttonXOffset = button.attr("buttonXOffset");
            if (buttonXOffset) {
                xOffset += parseInt(buttonXOffset);
            }

            var buttonYOffset = button.attr("buttonYOffset");
            if (buttonYOffset) {
                yOffset += parseInt(buttonYOffset);
            }

            button.css("top", buttonContainer.position().top + yOffset);
            button.css("left", buttonContainer.position().left + xOffset);
        });
    };

    setInterval(updateButtonsPosition, 200);

    $.fn.drafts = function (options) {
        var settings = $.extend({
            textDrafts: 'Drafts',
            textUseIt: 'Use it',
            url: '/data/drafts.php',
            pollDelay: 5000,
            showDelay: 2500,
            saveErrorMessage: "Can't save draft. Possibly connection is lost or session is expired. Stay on the page (cancel to reload)?",
            useItHandler: function (textarea, text) {
                textarea.val(text);
            }
        });
    
        $.extend(settings, {
            saveErrorHandler: function () {
                if (!confirm(settings["saveErrorMessage"])) {
                    location.reload();
                }
            }
        });
        
        $.extend(settings, options);

        var textareas = this;
        setTimeout(function () {
            textareas.each(function () {
                var textarea = $(this);
                if (textarea.parent()[0].tagName.toLowerCase() === "arclones") {
                    return;
                }

                if ($(".drafts-prototype").length === 0) {
                    $("<div class=\"drafts-prototype drafts-show-drafts\"><span class=\"drafts-button drafts-online\">"
                        + settings["textDrafts"]
                        + "</span></div>").appendTo($("body"));
                }

                if ($(".drafts-popup").length === 0) {
                    $("<div class=\"drafts-popup\"><div class=\"drafts-close\">&times;</div><h1>"
                        + settings["textDrafts"]
                        + "</h1><div class=\"drafts-entries\"></div></div>").appendTo($("body"));
                }

                if (textarea.prop("tagName").toLowerCase() != "textarea") {
                    $.error("jquery.drafts.js can be used only for textareas, but " + textarea.prop("tagName").toLowerCase() + " found.");
                }

                if (!textarea.attr("data-drafts-id")) {
                    $.error("jquery.drafts.js requires textarea to have attribute data-drafts-id.");
                }

                var id = textarea.attr("data-drafts-id");

                var button = $(".drafts-prototype").clone()
                    .removeClass("drafts-prototype")
                    .css("opacity", "0.2");

                button.mouseover(function () {
                    button.css("opacity", "1.0");
                });

                button.mouseleave(function () {
                    button.css("opacity", "0.2");
                });

                button.click(function () {
                    var popup = $(".drafts-popup");
                    var entries = popup.find(".drafts-entries");
                    $.post(settings["url"], {action: 'get', id: id}, function (items) {
                        entries.empty();
                        $.each(items, function (index, item) {
                            $("<pre class='drafts-entry-body'></pre>").text(item).appendTo(entries);
                            $("<div class='drafts-entry-actions'><span class='drafts-button'>" + settings["textUseIt"] + "</span></div>").appendTo(entries);
                        });
                        entries.find(".drafts-button").click(function () {
                            settings["useItHandler"](textarea, $(this).parent().prev().text());
                            $(".drafts-popup").fadeOut();
                        });
                        popup.show();
                        popup.css("top", pageYOffset);
                    }, "json");
                });

                var buttonXOffset = settings["buttonXOffset"];
                if (buttonXOffset) {
                    button.attr("buttonXOffset", buttonXOffset);
                }

                var buttonYOffset = settings["buttonYOffset"];
                if (buttonYOffset) {
                    button.attr("buttonYOffset", buttonYOffset);
                }

                var buttonContainerSelector = settings["buttonContainerSelector"];
                if (buttonContainerSelector && buttonContainerSelector.length > 0) {
                    button.attr("buttonContainerSelector", buttonContainerSelector);
                    $($(buttonContainerSelector)[0]).append(button);
                } else {
                    $(textarea.parent()).append(button);
                }

                button.css("position", "absolute");

                textareasToListen.push(textarea);
                buttonsToListen.push(button);
                updateButtonsPosition();

                $(".drafts-popup .drafts-close").click(function () {
                    $(".drafts-popup").fadeOut();
                });

                window.setInterval(function () {
                    var text = textarea.val();
                    var innerButton = button.find(".drafts-button");
                    $.post(settings["url"], {action: 'put', id: id, text: text}, function (response) {
                        if (response === "OK") {
                            consecutiveFailCount = 0;
                            if (!innerButton.hasClass("drafts-online")) {
                                innerButton.removeClass("drafts-offline");
                                innerButton.addClass("drafts-online");
                            }
                        } else {
                            ++consecutiveFailCount;
                            if (!innerButton.hasClass("drafts-offline")) {
                                innerButton.removeClass("drafts-online");
                                innerButton.addClass("drafts-offline");
                            }
                            if (consecutiveFailCount >= 5 * textareasToListen.length && !alertedOnFail) {
                                alertedOnFail = true;
                                settings["saveErrorHandler"]();
                            }
                        }
                    }, "json").fail(function () {
                            ++consecutiveFailCount;
                            if (!innerButton.hasClass("drafts-offline")) {
                                innerButton.removeClass("drafts-online");
                                innerButton.addClass("drafts-offline");
                            }
                            if (consecutiveFailCount >= 5 * textareasToListen.length && !alertedOnFail) {
                                alertedOnFail = true;
                                settings["saveErrorHandler"]();
                            }
                        });
                }, settings["pollDelay"]);
            });
        }, settings["showDelay"]);

        return this;
    };
})(jQuery);
