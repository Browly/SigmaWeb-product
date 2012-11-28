
historicalBarChart = [
	{
		key: "Cumulative Return",
		values: [
		]
	}
];

for (var item in put) {
	historicalBarChart[0].values.push({
		"label" : item,
		"value" : put[item]
	});
}
	


nv.addGraph(function() {  
  var chart = nv.models.discreteBarChart()
      .x(function(d) { return d.label })
      .y(function(d) { return d.value })
      .staggerLabels(true)
      //.staggerLabels(historicalBarChart[0].values.length > 8)
      .tooltips(false)
      .showValues(true)

  d3.select('#chart1 svg')
      .datum(historicalBarChart)
    .transition().duration(500)
      .call(chart);

  nv.utils.windowResize(chart.update);

  return chart;
});

