(function ($) {
  var queryParser = function (a) {
      var i, p, b = {};
      if (a === "") {
        return {};
      }
      for (i = 0; i < a.length; i += 1) {
        p = a[i].split('=');
        if (p.length === 2) {
          b[p[0]] = decodeURIComponent(p[1].replace(/\+/g, " "));
        }
      }
      return b;
    };
  $.queryParams = function () {
    return queryParser(window.location.search.substr(1).split('&'));
  };
  $.hashParams = function () {
    return queryParser(window.location.hash.substr(1).split('&'));
  };


  var ident = 0;

  window.TinySou = window.TinySou || {};

  // Functions used to track result click event
  TinySou.pingUrl = function(endpoint, callback) {
    var to = setTimeout(callback, 350);
    var img = new Image();
    img.onload = img.onerror = function() {
      clearTimeout(to);
      callback();
    };
    img.src = endpoint;
    return false;
  };
  TinySou.pingSearchResultClick = function (engineKey, collection, docId, callback) {
    var params = {
      t: new Date().getTime(),
      c: collection,
      doc_id: docId,
      q: TinySou.currentQuery
    };
    var url = uojHome + '/tinysou/pc?' + $.param(params);
    TinySou.pingUrl(url, callback);
  };

  TinySou.pingAutoSelection = function(engineKey, collection, docId, value, callback) {
    var params = {
      t: new Date().getTime(),
      c: collection,
      doc_id: docId,
      prefix: value
    };
    var url = uojHome + '/tinysou/pas?' + $.param(params);
    TinySou.pingUrl(url, callback);
  };

  TinySou.findSelectedSection = function() {
    var sectionText = $.hashParams().sts;
    if (!sectionText) { return; }

    function normalizeText(str) {
      // var out = str.replace(/\s+/g, '');
      // out = out.toLowerCase();
      // return out;
      return str.replace(/\s+/g, '').toLowerCase();
    }

    sectionText = normalizeText(sectionText);

    $('h1, h2, h3, h4, h5, h6').each(function(idx) {
      // no 'var'
      $this = $(this);
      if (normalizeText($this.text()).indexOf(sectionText) >= 0) {
        this.scrollIntoView(true);
        return false;
      }
    });
  };

  TinySou.htmlEscape = TinySou.htmlEscape || function htmlEscape(str) {
    return String(str).replace(/&/g, '&amp;').replace(/"/g, '&quot;').replace(/'/g, '&#39;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
  };

  $.fn.tinysouSearch = function (options) {
    var options = $.extend({}, $.fn.tinysouSearch.defaults, options);

    return this.each(function () {
      var $this = $(this);
      var config = $.meta ? $.extend({}, options, $this.data()) : options;

      $this.data('tinysou-config-search', config);
      $this.selectedCallback = function (data) {
        return function (e) {
          var $el = $(this);
          e.preventDefault();
          TinySou.pingSearchResultClick(config.engineKey, data['collection'], data['document']['id'], function() {
            window.location = $el.attr('href');
          });
        };
      };

      $this.selectedActCallback = function(data) {
        return function() {
          var value = $this.val(),
            callback = function() {
              config.onComplete(data, value);
            };
          TinySou.pingAutoSelection(config.engineKey, data['collection'], data['document']['id'], value, callback);
        };
      };

      $this.registerResult = function ($element, data) {
        $element.data('tinysou-item', data);
        $('a', $element).click($this.selectedCallback(data));
      };

      $this.registerActResult = function($element, data) {
        $element.data('tinysou-item', data);
        $element.click($this.selectedActCallback(data)).mouseover(function () {
          $this.listResults().removeClass(config.activeItemClass);
          $element.addClass(config.activeItemClass);
        });
      };

      $this.abortCurrent = function() {
        if ($this.currentRequest) {
          $this.currentRequest.abort();
        }
      };

      $this.showList = function() {
        if (handleFunctionParam(config.disableAutocomplete) === false) {
          $listContainer.show();
        }
      };

      $this.hideList = function(sync) {
        if (sync) {
          $listContainer.hide();
        } else {
          setTimeout(function() { $listContainer.hide(); }, 10);
        }
      };

      $this.focused = function() {
        return $this.is(':focus');
      };

      $this.submitting = function() {
        $this.submitted = true;
      };

      $this.listResults = function() {
        return $(config.resultListSelector, $list);
      };

      $this.activeResult = function() {
        return $this.listResults().filter('.' + config.activeItemClass).eq(0);
      };

      $this.prevResult = function() {
        var list = $this.listResults(),
          currentIdx = list.index($this.activeResult()),
          nextIdx = currentIdx - 1,
          next = list.eq(nextIdx);
        $this.listResults().removeClass(config.activeItemClass);
        if (nextIdx >= 0) {
          next.addClass(config.activeItemClass);
        }
      };

      $this.nextResult = function() {
        var list = $this.listResults(),
          currentIdx = list.index($this.activeResult()),
          nextIdx = currentIdx + 1,
          next = list.eq(nextIdx);
        $this.listResults().removeClass(config.activeItemClass);
        if (nextIdx >= 0) {
          next.addClass(config.activeItemClass);
        }
      };
      $this.styleDropdown = function() {
        $listContainer.css(config.dropdownStylesFunction($this));
      };

      $(window).resize(function (event) {
        $this.styleDropdown();
      });
      $this.isEmpty = function(query) {
        return $.inArray(normalize(query), this.emptyQueries) >= 0;
      };

      $this.addEmpty = function(query) {
        $this.emptyQueries.unshift(normalize(query));
      };
      $this.getContentCache = function () {
        return $('#' + contentCacheId);
      };

      var $resultContainer;
      if (config.renderStyle == 'inline') {
        $resultContainer = $(config.resultContainingElement);
      } else if (config.renderStyle == 'new_page') {
        $resultContainer = $(config.resultContainingElement);
        var url = window.location.pathname;
        if (url == config.resultPageURL) {
          config.renderStyle = 'inline';
        }
      } else {
        $('body').append("<div id='ts-results-container' style='display: none;'></div>");
        $resultContainer = $('#ts-results-container');
      }
      var initialContentOfResultContainer = $resultContainer.html(),
        contentCacheId = 'ts-content-cache',
        $contentCache = $this.getContentCache();

      var setSearchHash = function (query, page) {
          location.hash = "tsq=" + encodeURIComponent(query) + "&tsp=" + page;
          $(window).trigger('hashchange');
        };

      var submitSearch = function (query, options) {
          options = $.extend({
            page: 1
          }, options);
          var params = {};

          if (!$contentCache.length) {
            $resultContainer.after("<div id='" + contentCacheId + "' style='display: none;'></div>");
            $contentCache.html(initialContentOfResultContainer).hide();
          }
          config.loadingFunction(query, $resultContainer);

          TinySou.currentQuery = query;
          params['q'] = query;
          params['page'] = options.page;
          params['per_page'] = config.perPage;

          function handleFunctionParam(field) {
            // if (field !== undefined) {
            //   var evald = field;
            //   if (typeof evald === 'function') {
            //     evald = evald.call();
            //   }
            //   return evald;
            // }
            // return undefined;
            return typeof field === 'function' ? field() : field;
          }

          params['search_fields'] = handleFunctionParam(config.searchFields);
          params['fetch_fields'] = handleFunctionParam(config.fetchFields);
          params['facets'] = handleFunctionParam(config.facets);
          params['filter'] = handleFunctionParam(config.filter);
          params['c'] = handleFunctionParam(config.collection);
          params['sort'] = handleFunctionParam(config.sort);
          $.getJSON(uojHome + "/tinysou/search?callback=?", params).success(renderSearchResults);
        };
      $(window).on('hashchange', function () {
        var params = $.hashParams();
        if (params.tsq) {
          submitSearch(params.tsq, {
            page: params.tsp
          });
        } else {
          var $contentCache = $this.getContentCache();
          if ($contentCache.length) {
            $resultContainer.html($contentCache.html());
            $contentCache.remove();
          }
        }
      });

      var $containingForm = $this.parents('form');
      if ($containingForm) {
        $containingForm.bind('submit', function (e) {
          e.preventDefault();
          var searchQuery = $this.val();
          setSearchHash(searchQuery, 1);
        });
      }

      $(document).on('click', '[data-hash][data-page]', function (e) {
        e.preventDefault();
        var $this = $(this);
        setSearchHash($.hashParams().tsq, $this.data('page'));
      }).on('click', '[data-hash][data-spelling-suggestion]', function (e) {
        e.preventDefault();
        var $this = $(this);
        setSearchHash($this.data('spelling-suggestion'), 1);
      });

      var renderSearchResults = function (data) {
        if (typeof config.preRenderFunction === 'function') {
          config.preRenderFunction.call($this, data);
        }

        config.renderResultsFunction($this.getContext(), data);

        if (typeof config.postRenderFunction === 'function') {
          config.postRenderFunction.call($this, data);
        }
      };

      $this.getContext = function () {
        return {
          config: config,
          resultContainer: $resultContainer,
          registerResult: $this.registerResult
        };
      };

      $this.getActContext = function() {
        return {
          config: config,
          list: $list,
          registerActResult: $this.registerActResult
        };
      };
      $this.attr('autocomplete', 'off');
      $this.data('tinysou-config-autocomplete', config);
      $this.submitted = false;
      $this.cache = new LRUCache(10);
      $this.emptyQueries = [];

      var styles = config.dropdownStylesFunction($this);
      var $tinysouWidget = $('<div class="tinysou-widget" />');
      var $listContainer = $('<div />').addClass(config.autocompleteListClass).appendTo($tinysouWidget).css(styles).hide();
      $tinysouWidget.appendTo(config.autocompleteContainingElement);
      var $list = $('<' + config.autocompleteListType + ' />').appendTo($listContainer);

      $this.data('tinysou-list', $list);
      var typingDelayPointer;
      var suppressKey = false;
      $this.lastValue = '';
      //bind event listener
      $this.keyup(function (event) {
        if (suppressKey) {
          suppressKey = false;
          return;
        }

        // ignore arrow keys, shift
        if (((event.which > 36) && (event.which < 41)) || (event.which == 16)) return;

        if (config.typingDelay > 0) {
          clearTimeout(typingDelayPointer);
          typingDelayPointer = setTimeout(function () {
            processInput($this);
          }, config.typingDelay);
        } else {
          processInput($this);
        }
      });
      $this.keydown(function (event) {
        $this.styleDropdown();
        // enter = 13; up = 38; down = 40; esc = 27
        var $active = $this.activeResult();
        switch (event.which) {
        case 13:
          if (($active.length !== 0) && ($list.is(':visible'))) {
            event.preventDefault();
            $this.selectedActCallback($active.data('tinysou-item'))();
          } else if ($this.currentRequest) {
            $this.submitting();
          }
          $this.hideList();
          suppressKey = true;
          break;
        case 38:
          event.preventDefault();
          if ($active.length === 0) {
            $this.listResults().eq(-1).addClass(config.activeItemClass);
          } else {
            $this.prevResult();
          }
          break;
        case 40:
          event.preventDefault();
          if ($active.length === 0) {
            $this.listResults().eq(0).addClass(config.activeItemClass);
          } else if ($active != $this.listResults().eq(-1)) {
            $this.nextResult();
          }
          break;
        case 27:
          $this.hideList();
          suppressKey = true;
          break;
        default:
          $this.submitted = false;
          break;
        }
      });

      // opera wants keypress rather than keydown to prevent the form submit
      // so bind keypress event for opera-only should be better(?)
      // http://browserhacks.com/#op
      // (!!window.opera || /opera|opr/i.test(navigator.userAgent)) &&
      $this.keypress(function (event) {
        if ((event.which == 13) && ($this.activeResult().length > 0)) {
          event.preventDefault();
        }
      });
      // stupid hack to get around loss of focus on mousedown
      var mouseDown = false;
      var blurWait = false;
      $(document).bind('mousedown.tinysou' + ++ident, function () {
        mouseDown = true;
      }).bind('mouseup.tinysou' + ident, function () {
        mouseDown = false;
        if (blurWait) {
          blurWait = false;
          $this.hideList();
        }
      });
      $this.blur(function () {
        if (mouseDown) {
          blurWait = true;
        } else {
          $this.hideList();
        }
      });
      $this.focus(function () {
        setTimeout(function() { $this.select(); }, 10);
        if ($this.listResults().filter(':not(.' + config.noResultsClass + ')').length > 0) {
          $this.showList();
        }
      });
      $(window).trigger('hashchange');
    });
  };


  var renderPagination = function (ctx, resultInfo) {
    var pages = '<div class="ts-page">',
        previousPage, nextPage, currentPage, totalPages;
    currentPage = resultInfo['page'];
    totalPages = resultInfo['total_pages'];
    if (currentPage > 1) {
      previousPage = currentPage - 1;
      pages = pages + '<a href="#" class="ts-prev" data-hash="true" data-page="' + previousPage + '">&laquo; 上一页</a>';
    }
    if (currentPage < totalPages) {
      nextPage = currentPage + 1;
      pages = pages + '<a href="#" class="ts-next" data-hash="true" data-page="' + nextPage + '">下一页 &raquo;</a>';
    }
    pages += '<span class="ts-position-right ts-small">Powered by <a href="http://tinysou.com">@tinysou</a></span></div>';
    if (currentPage <= 1 && currentPage >= totalPages) {
      pages = '<div class="ts-page ts-right ts-small">Powered by <a href="http://tinysou.com">@tinysou</a></div></div>';
    }
    $(pages).appendTo(ctx.resultContainer);
  };


  var normalize = function (str) {
      return $.trim(str).toLowerCase();
    };

  var callRemote = function ($this, term) {
    $this.abortCurrent();

    var params = {},
      config = $this.data('tinysou-config-autocomplete');

    params['q'] = term;
    params['search_fields'] = handleFunctionParam(config.searchFields);
    params['fetch_fields'] = handleFunctionParam(config.fetchFields);
    params['filter'] = handleFunctionParam(config.filter);
    params['c'] = handleFunctionParam(config.collection);
    params['sort'] = handleFunctionParam(config.sort);
    params['per_page'] = config.resultLimit;

    var endpoint = uojHome + '/tinysou/autocomplete';
    $this.currentRequest = $.ajax({
      type: 'GET',
      dataType: 'jsonp',
      url: endpoint,
      data: params
    }).success(function(data) {
      if (data.rp !== undefined) {
        return;
      }
      var norm = normalize(term);
      if (data.info.total > 0) {
        $this.cache.put(norm, data.records);
      } else {
        $this.addEmpty(norm);
        $this.data('tinysou-list').empty();
        $this.hideList();
        return;
      }
      processData($this, data.records, term);
    });
  };

  var getResults = function($this, term) {
    var norm = normalize(term);
    if ($this.isEmpty(norm)) {
      $this.data('tinysou-list').empty();
      $this.hideList();
      return;
    }
    var cached = $this.cache.get(norm);
    if (cached) {
      processData($this, cached, term);
    } else {
      callRemote($this, term);
    }
  };
  // private helpers
  var processInput = function ($this) {
      var term = $this.val();
      if (term === $this.lastValue) {
        return;
      }
      $this.lastValue = term;
      if (!$.trim(term)) {
        $this.data('tinysou-list').empty();
        $this.hideList();
        return;
      }
      if (typeof $this.data('tinysou-config-autocomplete').engineKey !== 'undefined') {
        getResults($this, term);
      }
    };

  var processData = function ($this, data, term) {
    var $list = $this.data('tinysou-list'),
      config = $this.data('tinysou-config-autocomplete');

    $list.empty();
    $this.hideList(true);

    config.renderActResultsFunction($this.getActContext(), data);

    var totalItems = $this.listResults().length;
    if ((totalItems > 0 && $this.focused()) || (config.noResultsMessage !== undefined)) {
      if ($this.submitted) {
        $this.submitted = false;
      } else {
        $this.showList();
      }
    }
  };

  var defaultRenderResultsFunction = function (ctx, data) {
    var $resultContainer = ctx.resultContainer,
      config = ctx.config;

    $resultContainer.html('');
    
    if (data.rp !== undefined) {
	  $resultContainer.html(data.rp);
	} else {
      $.each(data.records, function (idx, item) {
        ctx.registerResult($(config.renderFunction(item)).appendTo($resultContainer), item);
      });
    
      if (data.records.length == 0) {
        $resultContainer.append("<p>无搜索结果</p>");
      }

      renderPagination(ctx, data.info);
	}
	
    if (!config.renderStyle) {
      $('#ts-results-container').appendTo('body').ts_modal({zIndex: 9999});
    } else if (config.renderStyle == 'new_page') {
      var url = config.resultPageURL + window.location.hash;
      window.location.replace(url);
    }
  };

  var defaultRenderFunction = function (item) {
      var title = item['document']['title'];
      var url = item['document']['url'];
      var body = (item.highlight && item.highlight['body']) || item['document']['sections'];
      return '<div class="ts-result"><h3 class="title"><a href='+ url + ' class="ts-search-result-link">' + title + '</a></h3><div class="ts-metadata"><span class="ts-snippet">' + body + '</span></div></div>';
    };

  var defaultLoadingFunction = function(query, $resultContainer) {
      $resultContainer.html('<p class="ts-loading-message">loading...</p>');
    };

  var defaultRenderActResultsFunction = function(ctx, results) {
    var $list = ctx.list,
      config = ctx.config;

    $.each(results, function(idx, item) {
      ctx.registerActResult($('<li>' + config.renderActFunction(item) + '</li>').appendTo($list), item);
    });
  };

  var defaultRenderActFunction = function(item) {
    return '<p class="title">' + TinySou.htmlEscape(item['document']['title']) + '</p>';
  };

  var defaultOnComplete = function(item, prefix) {
    window.location = item['document']['url'];
  };

  var defaultDropdownStylesFunction = function($this) {
    var config = $this.data('tinysou-config-autocomplete');
    var $attachEl = config.attachTo ? $(config.attachTo) : $this;
    var offset = $attachEl.offset();
    var styles = {
      'position': 'absolute',
      'z-index': 9999,
      'top': offset.top + $attachEl.outerHeight() + 1,
      'left': offset.left
    };

    if (config.setWidth) {
      styles['width'] = $attachEl.outerWidth() - 2;
    }
    return styles;
  };
  var handleFunctionParam = function(field) {
    // if (field !== undefined) {
    //   var evald = field;
    //   if (typeof evald === 'function') {
    //     evald = evald.call();
    //   }
    //   return evald;
    // }
    // return undefined;
    return typeof field === 'function' ? field() : field;
  };
  // simple client-side LRU Cache, based on https://github.com/rsms/js-lru

  function LRUCache(limit) {
    this.size = 0;
    this.limit = limit;
    this._keymap = {};
  }

  LRUCache.prototype.put = function (key, value) {
    var entry = {
      key: key,
      value: value
    };
    this._keymap[key] = entry;
    if (this.tail) {
      this.tail.newer = entry;
      entry.older = this.tail;
    } else {
      this.head = entry;
    }
    this.tail = entry;
    if (this.size === this.limit) {
      return this.shift();
    } else {
      this.size++;
    }
  };

  LRUCache.prototype.shift = function () {
    var entry = this.head;
    if (entry) {
      if (this.head.newer) {
        this.head = this.head.newer;
        this.head.older = undefined;
      } else {
        this.head = undefined;
      }
      entry.newer = entry.older = undefined;
      delete this._keymap[entry.key];
    }
    return entry;
  };

  LRUCache.prototype.get = function (key, returnEntry) {
    var entry = this._keymap[key];
    if (entry === undefined) return;
    if (entry === this.tail) {
      return entry.value;
    }
    if (entry.newer) {
      if (entry === this.head) this.head = entry.newer;
      entry.newer.older = entry.older;
    }
    if (entry.older) entry.older.newer = entry.newer;
    entry.newer = undefined;
    entry.older = this.tail;
    if (this.tail) this.tail.newer = entry;
    this.tail = entry;
    return returnEntry ? entry : entry.value;
  };

  LRUCache.prototype.remove = function (key) {
    var entry = this._keymap[key];
    if (!entry) return;
    delete this._keymap[entry.key];
    if (entry.newer && entry.older) {
      entry.older.newer = entry.newer;
      entry.newer.older = entry.older;
    } else if (entry.newer) {
      entry.newer.older = undefined;
      this.head = entry.newer;
    } else if (entry.older) {
      entry.older.newer = undefined;
      this.tail = entry.older;
    } else {
      this.head = this.tail = undefined;
    }

    this.size--;
    return entry.value;
  };

  LRUCache.prototype.clear = function () {
    this.head = this.tail = undefined;
    this.size = 0;
    this._keymap = {};
  };

  // if (typeof Object.keys === 'function') {
  //   LRUCache.prototype.keys = function () {
  //     return Object.keys(this._keymap);
  //   };
  // } else {
  //   LRUCache.prototype.keys = function () {
  //     var keys = [];
  //     for (var k in this._keymap) keys.push(k);
  //     return keys;
  //   };
  // }
  LRUCache.prototype.keys = Object.keys ? function(){
    return Object.keys( this._keymap );
  } : function(){
    var keys = [];
    for (var k in this._keymap) keys.push(k);
    return keys;
  };
  $.fn.tinysouSearch.defaults = {
    attachTo: undefined,
    collection: 'page',
    filter: undefined,
    engineKey: undefined,
    searchFields: undefined,
    sort: undefined,
    fetchFields: ['title', 'url', 'sections'],
    renderStyle: undefined,
    resultPageURL: undefined,
    resultContainingElement: undefined,
    preRenderFunction: undefined,
    postRenderFunction: undefined,
    loadingFunction: defaultLoadingFunction,
    renderResultsFunction: defaultRenderResultsFunction,
    renderFunction: defaultRenderFunction,
    perPage: 10,
    //autocomplete
    activeItemClass: 'active',
    noResultsClass: 'noResults',
    noResultsMessage: undefined,
    onComplete: defaultOnComplete,
    renderActResultsFunction: defaultRenderActResultsFunction,
    renderActFunction: defaultRenderActFunction,
    dropdownStylesFunction: defaultDropdownStylesFunction,
    resultLimit: 5,
    autocompleteListType: 'ul',
    autocompleteListClass: 'autocomplete',
    resultListSelector: 'li',
    setWidth: true,
    typingDelay: 80,
    disableAutocomplete: false,
    autocompleteContainingElement: 'body'
  };
})(jQuery);
