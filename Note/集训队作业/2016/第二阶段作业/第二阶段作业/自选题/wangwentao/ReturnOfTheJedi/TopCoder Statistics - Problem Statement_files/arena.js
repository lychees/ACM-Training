
var detectableWithVB = false;
var pluginFound = false;

function goURL(daURL) {
   window.location = daURL;
   return;
}

function redirectCheck(pluginFound, redirectURL, redirectIfFound) {
    if( redirectURL && ((pluginFound && redirectIfFound) ||
   (!pluginFound && !redirectIfFound)) ) {
   goURL(redirectURL);
   return pluginFound;
    } else {
   return pluginFound;
    }
}

function canDetectPlugins() {
    if( detectableWithVB || (navigator.plugins && navigator.plugins.length > 0) ) {
   return true;
    } else {
   return false;
    }
}

function detectJavaWebStartWithMimeTypes() {
    if (navigator.mimeTypes && navigator.mimeTypes.length) {
        if (navigator.mimeTypes['application/x-java-jnlp-file']) {
            return true;
        }
    }
    return false;
}

function detectJavaWebStart(redirectURL, redirectIfFound) {
    pluginFound = detectJavaWebStartWithMimeTypes();
    if(!pluginFound && detectableWithVB) {
   pluginFound = detectActiveXControl('JavaWebStart.isInstalled');
    }
    return redirectCheck(pluginFound, redirectURL, redirectIfFound);
}

function detectJava(redirectURL, redirectIfFound) {
    pluginFound = detectPlugin('Java','Plug-in');
    if(!pluginFound && detectableWithVB) {
   pluginFound = detectActiveXControl('JavaPlugin');
    }
    return redirectCheck(pluginFound, redirectURL, redirectIfFound);
}

function detectPlugin() {
    var daPlugins = detectPlugin.arguments;
    var pluginFound = false;
    if (navigator.plugins && navigator.plugins.length > 0) {
   var pluginsArrayLength = navigator.plugins.length;
   for (pluginsArrayCounter=0; pluginsArrayCounter < pluginsArrayLength; pluginsArrayCounter++ ) {
       var numFound = 0;
       for(namesCounter=0; namesCounter < daPlugins.length; namesCounter++) {
      if( (navigator.plugins[pluginsArrayCounter].name.indexOf(daPlugins[namesCounter]) >= 0) ||
          (navigator.plugins[pluginsArrayCounter].description.indexOf(daPlugins[namesCounter]) >= 0) ) {
         numFound++;
      }
       }
       if(numFound == daPlugins.length) {
      pluginFound = true;
      break;
       }
   }
    }
    return pluginFound;
}

if ((navigator.userAgent.indexOf('MSIE') != -1) && (navigator.userAgent.indexOf('Win') != -1)) {
    document.writeln('<script language="VBscript">');

    document.writeln('\'do a one-time test for a version of VBScript that can handle this code');
    document.writeln('detectableWithVB = False');
    document.writeln('If ScriptEngineMajorVersion >= 2 then');
    document.writeln('  detectableWithVB = True');
    document.writeln('End If');

    document.writeln('\'this next function will detect most plugins');
    document.writeln('Function detectActiveXControl(activeXControlName)');
    document.writeln('  on error resume next');
    document.writeln('  detectActiveXControl = False');
    document.writeln('  If detectableWithVB Then');
    document.writeln('     detectActiveXControl = IsObject(CreateObject(activeXControlName))');
    document.writeln('  End If');
    document.writeln('End Function');

    document.writeln('</scr' + 'ipt>');
}

   function arena() {
       if (canDetectPlugins()) {
           if (detectJavaWebStart()) {
               location='http://community.topcoder.com/contest/arena/ContestAppletProd.jnlp';
               return;
           }
           else {
               arenaApplet();
           }
       }
       else {
           arenaApplet();
       }
    }


   function arenaApplet() {
        w = window.open("http://community.topcoder.com/tc?module=Static&d1=applet&d2=detect", "Launch", "top=2,left=2,width=400,height=400,resizable=yes,status=1");
        return;
    }




