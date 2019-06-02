const char timer_page[] PROGMEM = R"=====(
<!doctype htm>
<html>
<head>
	<meta charset="UTF-8">
	<script language="javascript" type="text/javascript" src="libraries/p5.js"></script>
	<script language="javascript" src="libraries/p5.dom.js"></script>
	<script language="javascript" src="libraries/p5.sound.js"></script>
	<script language="javascript" type="text/javascript" src="timer.js"></script>
	<style>
		@import url('https://fonts.googleapis.com/css?family=Roboto');
		body { font-family: 'Roboto', sans-serif; }
		#timer {
			color: #000;
			font-family: Arial;
			font-size: 30px;
		}
		button {
			text-decoration: none;
			color: #fff;
			background-color: #26a69a;
			text-align: center;
			letter-spacing: .5px;
			transition: .2s ease-out;
			cursor: pointer;
			border: none;
			border-radius: 2px;
			display: block;
			height: 36px;
			line-height: 36px;
			padding: 0 2rem;
			text-transform: uppercase;
			vertical-align: middle;
			-webkit-tap-highlight-color: transparent;
			box-shadow: 0 2px 2px 0 rgba(0,0,0,0.14), 0 1px 5px 0 rgba(0,0,0,0.12), 0 3px 1px -2px rgba(0,0,0,0.2);
		}
		button + button {
			margin-top: 10px;
		}
		button:focus {
			outline: 0;
		}
	</style>
</head>
<body>
	<p id="timer">______</p>
</body>
</html>
)=====";
