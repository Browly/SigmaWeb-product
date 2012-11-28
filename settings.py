info = {
    "team":   "Sigcake Sensation",
    "members":   "The Sensations",
    "description":  
        """This is a simulation demo of the classic NETWORKT model. 
           I hope you enjoy!""",
    "additional":
        """<h3>Additional Info:</h3>
        <ul>
            <li>Inventory Models</li>
            <li>Restock Bottleneck</li>
            <li>Employee Bottleneck</li>
            <li>LOREM IPSUM DOLOR</li>
            <li>LOREM IPSUM DOLOR</li>
        </ul>
        """
}
sigma = {
    "model": "SCSmod",    
    "runtime":{"name": "RUNTIME",
               "display": "Running Time",
               "default": 3000
              },
    "parameters": [
		{	"name": "INPUT[8]",
			"display": "Mean of exponential distribution for customer arrivals",
			"default": 10
		},
		
		{	"name": "INPUT[9]",
			"display": "Price of a cupcake",
			"default": 3.5
		},
		
		{	"name": "INPUT[12]",
			"display": "Number of Days Simulation is Run",
			"default": 7
		},
		
		{	"name": "INPUT[0]",
			"display": "Number of Workers",
			"default": 4
		},
		
		{	"name": "INPUT[1]",
			"display": "Number of Cash Registers",
			"default": 4
		},
		
		{	"name": "INPUT[2]",
			"display": "Number of Blenders",
			"default": 4
		},
		
		{	"name": "INPUT[3]",
			"display": "Number of Ovens",
			"default": 4
		},
		
		{	"name": "INPUT[10]",
			"display": "Amount of preparation time before store opens to customers each day",
			"default": 120
		},
		
		{	"name": "INPUT[11]",
			"display": "Amount of time the store is open to customers each day",
			"default": 360
		},
		
		{	"name": "INPUT[27]",
			"display": "Lower bound for number of cupcakes ordered (Uniform Distribution)",
			"default": 1
		},
		
		{	"name": "INPUT[28]",
			"display": "Upper bound for number of cupcakes ordered (Uniform Distribution)",
			"default": 10
		},
		
		{	"name": "THRESH[1:1]",
			"display": "Restocking threshold for Vanilla cupcakes",
			"default": 10.26
		},
		
		
		{	"name": "THRESH[1:2]",
			"display": "Restocking threshold for Chocolate cupcakes",
			"default": 10.26
		},
		
		
		{	"name": "THRESH[1:3]",
			"display": "Restocking threshold for Strawberry cupcakes",
			"default": 5.13
		},

		{	"name": "THRESH[2:1]",
			"display": "Restocking threshold for Vanilla filling",
			"default": 2.025
		},
		
		
		{	"name": "THRESH[2:2]",
			"display": "Restocking threshold for Chocolate filling",
			"default": 2.025
		},
		
		
		{	"name": "THRESH[2:3]",
			"display": "Restocking threshold for Strawberry filling",
			"default": 2.025
		},
		
		{	"name": "THRESH[3:1]",
			"display": "Restocking threshold for Vanilla frosting",
			"default": 1.35
		},
		
		
		{	"name": "THRESH[3:2]",
			"display": "Restocking threshold for Chocolate frosting",
			"default": 1.35
		},
		
		
		{	"name": "THRESH[3:3]",
			"display": "Restocking threshold for Strawberry frosting",
			"default": 1.35
		},
		
		{	"name": "THRESH[4:1]",
			"display": "Restocking threshold for Chocolate piece decoration",
			"default": 0.54
		},
		
		
		{	"name": "THRESH[4:2]",
			"display": "Restocking threshold for Fondant piece decoration",
			"default": 0.54
		},
		
		
		{	"name": "THRESH[4:3]",
			"display": "Restocking threshold for Custom (not store bought) Candy",
			"default": 0.54
		},
		
		{	"name": "CUSTPREF[1;1]",
			"display": "Probability customer orders Vanilla cupcakes",
			"default": .4
		},
		{	"name": "CUSTPREG[1;2]",
			"display": "Probability customer orders Chocolate cupcakes",
			"default": .4
		},
		{	"name": "CUSTPREG[1;3]",
			"display": "Probability customer orders Strawberry cupcakes",
                        "default": .2
		},
		{	"name": "CUSTPREG[2;0]",
			"display": "Probability customer doesn't orders any filling",
			"default": .1
		},
		{	"name": "CUSTPREG[2;1]",
			"display": "Probability customer orders Vanilla filling",
			"default": .3
		},
		{	"name": "CUSTPREG[2;2]",
			"display": "Probability customer orders Chocolate filling",
			"default": .3
		},
		{	"name": "CUSTPREG[2;3]",
			"display": "Probability customer orders Strawberry filling",
			"default": .3
		},
		{	"name": "CUSTPREG[3;0]",
			"display": "Probability customer doesn't order any frosting",
			"default": .1
		},
		{	"name": "CUSTPREG[3;1]",
			"display": "Probability customer orders Vanilla frosting",
			"default": .3
		},
		{	"name": "CUSTPREG[3;2]",
			"display": "Probability customer orders Chocolate frosting",
			"default": .3
		},
		{	"name": "CUSTPREG[3;3]",
			"display": "Probability customer orders Strawberry frosting",
			"default": .3
		},
		{	"name": "CUSTPREG[4;0]",
			"display": "Probability customer does order any decorations",
			"default": .1
		},
		{	"name": "CUSTPREG[4;1]",
			"display": "Probability customer orders Vanilla decorations",
			"default": .3
		},
		{	"name": "CUSTPREG[4;2]",
			"display": "Probability customer orders Chocolate decorations",
			"default": .3
		},
		{	"name": "CUSTPREG[4;3]",
			"display": "Probability customer orders Strawberry decorations",
			"default": .3
		},
		{	"name": "RESTOCKT[1;0]",
			"display": "Lower bound for cupcake restock (Beta)",
			"default": 30
		},
		{	"name": "RESTOCKT[1;1]",
			"display": "Upper bound for cupcake restock(Beta)",
			"default": 40
		},
		{	"name": "Alpha[1]",
			"display": "Alpha for cupcake restock (Beta)",
			"default": 2
		},
		{	"name": "Beta[1]",
			"display": "Beta for cupcake restock (Beta)",
			"default": 2
		},
		{	"name": "RESTOCKT[2;0]",
			"display": "Lower bound for Filling restock(Beta Distr)",
			"default": 12
		},
		{	"name": "RESTOCKT[2;1]",
			"display": "Upper bound for Filling restock(Beta Distr)",
			"default": 15
		},
		{	"name": "Alpha[2]",
			"display": "Alpha for filling restock (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[2]",
			"display": "Beta for filling restock (Beta Distr)",
			"default": 2
		},
		{	"name": "RESTOCKT[3;0]",
			"display": "Lower bound for Frosting restock(Beta Distr)",
			"default": 7
		},
		{	"name": "RESTOCKT[3;1]",
			"display": "Upper bound for Frosting restock(Beta Distr)",
			"default": 10
		},
		{	"name": "Alpha[3]",
			"display": "Alpha for Frosting restock (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[3]",
			"display": "Beta for Frosting restock (Beta Distr)",
			"default": 2
		},
		{	"name": "RESTOCKT[4;0]",
			"display": "Lower bound for Decoration restock(Beta Distr)",
			"default": 2
		},
		{	"name": "RESTOCKT[4;1]",
			"display": "Upper bound for Decoration restock(Beta Distr)",
			"default": 4
		},
		{	"name": "Alpha[4]",
			"display": "Alpha for decoration restock (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[4]",
			"display": "Beta for Decoration restock (Beta Distr)",
			"default": 2
		},
		{	"name": "SERVICET[0;0]",
			"display": "Lower bound for cashier service restock(Beta Distr)",
			"default": 1
		},
		{	"name": "SERVICET[0;1]",
			"display": "Upper bound for cashier service(Beta Distr)",
			"default": 3
		},
		{	"name": "Alpha[5]",
			"display": "Alpha for cashier service (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[5]",
			"display": "Beta for cashier service (Beta Distr)",
			"default": 2
		},
		{	"name": "SERVICET[1;0]",
			"display": "Lower bound for cupcake service restock(Beta Distr)",
			"default": 0.2
		},
		{	"name": "SERVICET[1;1]",
			"display": "Upper bound for cupcake service(Beta Distr)",
			"default": 1
		},
		{	"name": "Alpha[6]",
			"display": "Alpha for cupcake service (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[6]",
			"display": "Beta for cupcake service (Beta Distr)",
			"default": 2
		},
		{	"name": "SERVICET[2;0]",
			"display": "Lower bound for filling service restock(Beta Distr)",
			"default": 0.5
		},
		{	"name": "SERVICET[2;1]",
			"display": "Upper bound for filling service(Beta Distr)",
			"default": 2
		},
		{	"name": "Alpha[7]",
			"display": "Alpha for filling service (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[7]",
			"display": "Beta for filling service (Beta Distr)",
			"default": 2
		},
		{	"name": "SERVICET[3;0]",
			"display": "Lower bound for frosting service restock(Beta Distr)",
			"default": 0.5
		},
		{	"name": "SERVICET[3;1]",
			"display": "Upper bound for frosting service(Beta Distr)",
			"default": 2
		},
		{	"name": "Alpha[8]",
			"display": "Alpha for frosting service (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[8]",
			"display": "Beta for frosting service (Beta Distr)",
			"default": 2
		},
		{	"name": "SERVICET[4;0]",
			"display": "Lower bound for cashier service restock(Beta Distr)",
			"default": 0.5
		},
		{	"name": "SERVICET[4;1]",
			"display": "Upper bound for cashier service(Beta Distr)",
			"default": 2
		},
		{	"name": "Alpha[9]",
			"display": "Alpha for cashier service (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[9]",
			"display": "Beta for cashier service (Beta Distr)",
			"default": 2
		},
		{	"name": "INPUT[25]",
			"display": "Lower bound for cupcake restock preparation  service restock(Beta Distr)",
			"default": 13
		},
		{	"name": "INPUT[26]",
			"display": "Upper bound for cupcake restock preparation(Beta Distr)",
			"default": 17
		},
		{	"name": "Alpha[10]",
			"display": "Alpha for cupcake restock preparation (Beta Distr)",
			"default": 2
		},
		{	"name": "Beta[10]",
			"display": "Beta for cupcake restock preparation (Beta Distr)",
			"default": 2
		},
		{	"name": "INPUT[13]",
			"display": "Cost per unit for Vanilla cupcakes",
			"default": 0.51
		},
		{	"name": "INPUT[14]",
			"display": "Cost per unit for Chocolate cupcakes",
			"default": 0.61
		},
		{	"name": "INPUT[15]",
			"display": "Cost per unit for Strawberry cupcakes",
			"default": 0.5
		},
		{	"name": "INPUT[16]",
			"display": "Cost per unit for Vanilla filling",
			"default": 0.66
		},
		{	"name": "INPUT[17]",
			"display": "Cost per unit for Chocolate filling",
			"default": 0.5
		},
		{	"name": "INPUT[18]",
			"display": "Cost per unit for Strawberry filling",
			"default": 0.63
		},
		{	"name": "INPUT[19]",
			"display": "Cost per unit for Vanilla frosting",
			"default": 0.3
		},
		{	"name": "INPUT[20]",
			"display": "Cost per unit for Chocolate frosting",
			"default": 0.46
		},
		{	"name": "INPUT[21]",
			"display": "Cost per unit for Strawberry frosting",
			"default": 0.5
		},
		{	"name": "INPUT[22]",
			"display": "Cost per unit for Chocolate piece decoration",
			"default": 0.15
		},
		{	"name": "INPUT[23]",
			"display": "Cost per unit for Fondant piece decoration",
			"default": 0.15
		},
		{	"name": "INPUT[24]",
			"display": "Cost per unit for Custom Candy decoration",
			"default": 0.15
		},
		
		
    ]
		
}

graphs = [

	{   "name": "SUPPLY[1;1] vs. Time",
        "x-axis": "Time",
        "x-display": "Time (seconds)",
        "y-axis": "Time",
        "y-display": "Vanilla Batter Supply"
    },
	
	{   "name": "RESTOCK[1;1] vs. Time",
        "x-axis": "Time",
        "x-display": "Time (seconds)",
        "y-axis": "Time",
        "y-display": "Restocking the Vanilla"
    },

]

server = {
    "hostname": "localhost",
    "port": 9000
}
