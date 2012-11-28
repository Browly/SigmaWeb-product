var a = 1
var b = 1

var callback = function() {
	var chart = nv.models.lineWithFocusChart();
	chart.xAxis
          .tickFormat(d3.format(',.2f'))
          .axisLabel('x');
      chart.x2Axis
          .tickFormat(d3.format(',.2f'))


      chart.yAxis
          .tickFormat(d3.format(',.2f'))
          .axisLabel('y');
      chart.y2Axis
          .tickFormat(d3.format(',.2f'))

	d3.select('#test1')
		.datum([beta(a, b),])
		.transition().duration(500)
		.call(chart);
	nv.utils.windowResize(chart.update);
	return chart
	}
nv.addGraph(callback);

	
function beta(a, b) {
	graphData = {}
	graphData['key'] = [a.toFixed(2), b.toFixed(2)]
	graphData['values'] = []
	var scale = Math.sqrt(2*Math.PI)*(Math.pow(a,(a-.5))*Math.pow(b,(b-.5)))/(Math.pow((a+b),(a+b-.5)))
	for (var x = 0; x <=1; x+=.01){
		
		graphData['values'].push({"x": x, "y" : scale * Math.pow(x,a-1)*Math.pow((1-x),b-1)}); 
	}
	return graphData;
}

function incrementa() {
if (a < 3)
	a += 0.05
	document.getElementById('Alpha').value = a.toFixed(2);
	$("#test1").empty();
	nv.addGraph(callback);
}

function decreasea() {
if (a > 0.05)
	a -= 0.05
	$("#test1").empty();
	document.getElementById('Alpha').value = a.toFixed(2);
	nv.addGraph(callback);
}
function incrementb() {
if (b < 3)
	b += 0.05
	document.getElementById('Beta').value = b.toFixed(2);
	$("#test1").empty();
	nv.addGraph(callback);
}

function decreaseb() {
if (b > 0.05)
	b -= 0.05
	document.getElementById('Beta').value = b.toFixed(2);
	$("#test1").empty();
	nv.addGraph(callback);
}

function update(){
var a1 = parseFloat(document.getElementById('Alpha').value);
var b1 = parseFloat(document.getElementById('Beta').value);
if ( a1 != null)
	a = a1
if (b1 != null)
	b = b1
$("test1").empty();
nv.addGraph(callback);

}