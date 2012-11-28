//need this
nv.addGraph(function() {
  var chart = nv.models.scatterPlusLineChart()
                .showDistX(true)
                .showDistY(true)
                //.height(500)
                .color(d3.scale.category10().range());

  chart.xAxis.tickFormat(d3.format('.02f'))
  chart.yAxis.tickFormat(d3.format('.02f'))

  d3.select('#test1 svg')
      .datum(randomData(1,5))
    .transition().duration(500)
      .call(chart);

  nv.utils.windowResize(chart.update);

  return chart;
});


function randomData(groups, points) { //# groups,# points per group
  var data = [],
      shapes = ['circle'],
      random = d3.random.normal();

  for (i = 0; i < groups; i++) {
    data.push({
      key: 'Group ' + i,
      values: [],
      slope: 0,
      intercept: Math.random() - .5
    });

    for (j = 0; j < points; j++) {
      data[i].values.push({
        x: random(), 
        y: random(), 
        size: Math.random(), 
        shape: shapes[0]
      });
    }
  }

  return data;
}