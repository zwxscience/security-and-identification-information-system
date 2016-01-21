var isChrome = /Chrom/gi.test(window.navigator.userAgent);
var N = isChrome?28:80;
var Y = new Array();
var X = new Array();
var S = new Array();
var A = new Array();
var B = new Array();
var M = new Array();

var iH = 100;
var iW = 480;

for (i = 0; i < N; i++) {
	Y[i] = Math.round(Math.random() * iH);
	X[i] = Math.round(Math.random() * iW);
	S[i] = Math.round(Math.random() * 5 + 2);
	A[i] = 0;
	B[i] = Math.random() * 0.1 + 0.1;
	M[i] = Math.round(Math.random() * (isChrome?2:10) + 1);
}

function snow(){
	var head = document.getElementById("public-header");
	var wrap = document.createElement("div");
	wrap.style.cssText = "position:absolute;top:0;left:0; width:480px; height:100px; font-family:Arial";
	head.appendChild(wrap);

	for (i = 0; i < N; i++) {
		var div = document.createElement("div");
		div.id = "s" + i;
		div.style.cssText = 'position:absolute;top:0;left:0;width:' + M[i] + 'px;height:' + M[i] + 'px;color:#Fff;font-size:' + M[i] + 'px';
		div.innerHTML = isChrome?"❄":"※";
		wrap.appendChild(div);
	}
	setLink();
	moveSnow();
}

function setLink(){
	var els = document.getElementById("snow").getElementsByTagName("a");
	for(var i = 0; i < els.length; i++){
		els[i].onmouseover = (function(i){
			return function(){
				setLinkClass(i);
			}
		})(i)

		els[i].onmouseout = (function(i){
			return function(){
				setLinkClass();
			}
		})(i)
	}
}

function setLinkClass(num){
	var els = document.getElementById("public-nav").getElementsByTagName("a");
	for(var i = 0; i < els.length; i++){
		els[i].className = els[i].className.replace(/\s*h/g,"");
	}
	num!=null && (els[num].className += " h");
}

function moveSnow() {
	var H = iH;
	var W = iW;
	var T = document.body.scrollTop || document.documentElement.scrollTop;
	var L = document.body.scrollLeft || document.documentElement.scrollLeft;
	for (i = 0; i < N; i++) {
		sy = S[i] * Math.sin(90 * Math.PI / 180);
		sx = S[i] * Math.cos(A[i]);
		Y[i] += sy;
		X[i] += sx;
		if (Y[i] > H) {
			Y[i] = -10;
			X[i] = Math.round(Math.random() * W);
			M[i] = Math.round(Math.random() * 1 + 1);
			S[i] = Math.round(Math.random() * 5 + 2);
		}


			document.getElementById('s' + i).style.left = X[i] + "px";
			document.getElementById('s' + i).style.top = Y[i] + "px";

		A[i] += B[i];
	}
	setTimeout('moveSnow()', 85);
}

snow();