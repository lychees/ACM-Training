// Instance the tour
$(function(){
	var tour = new Tour({
		'backdrop': true,
		  'steps': [
		  {
			  element: "#problem-name",
			  title: "Step 1/6",
			  content: "Let's take a look at the example problem on SPOJ, named <i>Harry and big doughnuts</i>."
		  },
		  {
			  element: "#problem-body",
			  title: "Step 2/6",
			  content: "Each problem consists of: <ul><li>Problem description</li><li>Input description</li><li>Output description</li><li>and Example</li></ul> <p>Input and output data used by SPOJ judge to decide whether your solution is correct or not.</p><p>Many of problems has tricky test data so the ability to form you own and comprehensive test cases is very useful.</p>"
		  },
		  {
			  element: '#problem-meta',
			  title: "Step 3/6",
			  content: "Additional information: <ul class=\"list-unstyled\"><li><strong>Time limit</strong> - how long your solution can perform calculations; if your program doesn't end after specified time limit, you get the Time Limit Exceeded result</li><li><strong>Source limit</strong> - how big the solutions you upload can be</li><li><strong>Languages</strong> - which programming languages are allowed for the problem</li></ul>"
		  },
		  {
			  element: '#problem-btn-submit-box',
			  title: "Step 4/6",
			  content: "<p>After reading the description we find out that we need to help Harry... But what really matters to us is meaning of the numbers: c, k and w.</p><p>Old lady has c cats so Harry has to buy c doughnuts. Each weights w kilograms. Harry can carry only k kilograms. I guess everyone now knows how the correct formula looks like.</p><p><strong>Now let's try to solve it!</strong></p>",
		  },
		  {
			  path: "/submit/DOUGHNUT/#tour"
		  }
		  ],
		  'storage': false,
		  'onStart': function(tour){
			  ga('send', 'event', 'tour', 'tutorial', 'start');
		  },
		  'onShown': function(tour){
				if(tour.getCurrentStep() == 3){
					$('#problem-btn-submit').attr('href', '/submit/DOUGHNUT/#tour');
				}  
		  },
		  'onEnd': function(tour){
			  ga('send', 'event', 'tour', 'tutorial', 'end (1 page)');
		  }
	});
	
	var tour2 = new Tour({
		'backdrop': true,
		  'steps': [
		  {
			  element: "#file_div",
			  title: "Step 5/6",
			  content: "<p>Beginning:</p><pre>#include &lt;cstdio&gt;<br/>int main() {<br/></pre><p>Variables:</p><strong>t</strong> for multiple test cases<br/><strong>c, k, w</strong> for problem data<br/><pre>int t, c, k, w;</pre><p>Reading input and code end:</p><pre>scanf(\"%d\", &t);</br>while(t--) {</br>scanf(\"%d %d %d\", &c, &k, &w);<br/>if(c*w <= k)<br/>printf(\"yes\n\");<br/>else<br/>printf(\"no\n\");<br/>}<br/>return 0;<br/>}</pre>"
		  },
		  {
			  element: "form#submit_form",
			  title: "Step 6/6",
			  content: "<p>Either paste code into provided text field or upload source code from file. Then pick the language of your submission and click <strong>Send button</strong>.</p><p>You will be redirected to status page where you can watch the progress of judging your solution. After few moments you will see the result:</p>"
		  }
		  ],
		  'storage': false,
		  'onShown': function(tour){
				if(tour.getCurrentStep() == 1){
					var editor = ace.edit("file_div");
					editor.getSession().setValue('#include <cstdio>\nint main() {\n\tint t, c, k, w;\n\tscanf("%d", &t);\n\twhile(t--) {\n\t\tscanf("%d %d %d", &c, &k, &w);\n\t\tif(c*w <= k)\n\t\t\tprintf("yes\\n");\n\t\telse\n\t\t\tprintf("no\\n");\n\t}\n\treturn 0;\n}\n');
					$("#lang").val(1);
				}  
		  },
		  'onEnd': function(tour){
			  ga('send', 'event', 'tour', 'tutorial', 'end');
		  }
		  
	});
	
	var pathname = window.location.pathname;
	var hash = window.location.hash;
	
	if((pathname == '/problems/DOUGHNUT/' || pathname == '/problems/TEST/') && hash == '#tour'){
		tour.init();
		tour.start();
	}
	
	if((pathname == '/submit/DOUGHNUT/' || pathname == '/submit/TEST/') && hash == '#tour'){
		tour2.init();
		tour2.start();
	}
});