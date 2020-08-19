function updateGrid(r, c, state){
	var sel = "#" + r.toString()+ "-" + c.toString();
	

	if(state!=10){
		$(sel).removeClass("flag");
	}
	//if(state!=11){
		//$(sel).removeClass("falseflag");
	//}
	if (state==9){
		$(sel).addClass("bomb");
    }
    else if(state==10){
        $(sel).addClass("flag");
    }
    else if(state==11){
       $(sel).addClass("falseflag");
    }
    else if(state==12){
        $(sel).addClass("boom");
	}
	else if(state==-1){
		$(sel).addClass("cleanground");
	}
	else {
		$(sel).html(state);
	}
	
}

function  buttonBuild(i, j, state){
	if(state!=13){
	var sel ="#"+i.toString()+"-"+j.toString();
	
	$(sel).click(function(){
		//alert("Pay $20 for additional click dlc");
		if(state==13){
			$(sel).prop("disabled", true);
		}
		var left = "left";
		var location = {"x": i,"y": j,"btn":left};
		$.get("/handle",location, function(response){
		var data = JSON.parse(response);
		//alert("button pressed");
		for (var row in data){
			for (var col in data[row]){
				updateGrid(row, col, data[row][col]);
			}
		}
		if(state==13){
			$(sel).prop("disabled", true);}
		});
		
		//alert("Button" + sel +" id left clicked");
	});
	$(sel).contextmenu(function(e){
		e.preventDefault();
		//alert("Right click");
		var right = "right";
		$.get("/handle",{"x": i,"y": j,"btn":right}, function(response){
			//alert(response);
			var data = JSON.parse(response);
			for (var row in data){
				for (var col in data[row]){
					
					updateGrid(row, col, data[row][col]);
				}
			}
		});
		
		//alert("Button"+ sel+ " id right clicked");
	});
}
}

function createGrid(data){
	var result = "";

	for (var i in data){
		var cr = "<tr>";

		for (var j in data[i]){
			cr = cr + "<td id=\"" + i.toString()+ "-" + j.toString() + "\"></td>"
		}

		cr = cr + "</tr>\n";
		result = result + cr;
	}

	$("#grid").html(result);

	// Iterate over IDs, assign them a click handler
	for (var row in data){
		for (var col in data[row]){
			if(data[row][col]!=13){
				buttonBuild(row, col, data[row][col]);
			}
			else{
				$("#grid").prop("disabled",true);
			}
			updateGrid(row, col, data[row][col]);
		}
	}
}






$(document).ready(function(){
    $.get("/init", {}, function (response){
        var data = JSON.parse(response);
		createGrid(data);
		//$("#resetButton").html('<img src="o.png" class = "center" style="width:70px; height:70px">');
		//$("#aif").html('<img src= "mines.jpg" position: absolute; top 10px; style="width:57%; height:490px" >')
    
});


$("#resetButton").contextmenu(function(e){
	e.preventDefault();
	alert("Button right clicked");
});



$("#resetButton").click(function(){
    $.get("/init", {}, function (response){
        var data = JSON.parse(response);
        createGrid(data);
        for (var row in data){
			for (var col in data[row]){
				updateGrid(row, col, data[row][col]);
			}
		}

    });
});
	
});
