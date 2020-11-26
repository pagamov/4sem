'use strict'
new p5();

var background_color = '#F7F7F7';
var border_color = '#C5CBE3';
var start_color = '#F13C20';
var end_color = '#4056A1';
var block_color = '#D79522';
var void_color = '#EFE2BA';

var open_cell_color = '#BCE7FD';
var closed_cell_color = '#30475E';
var main_parent_color = '#6a097d';

var points = {start:null, end:null};

var board = [];
var curent_state = 'null';
var index_show = false;

function valid_cell(i, j) {
	if (i >= 0 && i < board.length && j >= 0 && j < board[i].length && board[i][j].closed != true && board[i][j].color != block_color) {
		 // removed form condition && board[i][j].open != true
		return true;
	}
	return false;
}

function find_close_cells(p_i, p_j) {
	var res = [];
	for (var i = 0; i < 3; i++) {
		if (valid_cell(p_i - 1 + i, p_j - 1)) {
			res.push({i:p_i - 1 + i, j:p_j - 1});
		}
	}

	if (valid_cell(p_i - 1, p_j)) {
		res.push({i:p_i - 1, j:p_j});
	}

	if (valid_cell(p_i + 1, p_j)) {
		res.push({i:p_i + 1, j:p_j});
	}

	for (var i = 0; i < 3; i++) {
		if (valid_cell(p_i - 1 + i, p_j + 1)) {
			res.push({i:p_i - 1 + i, j:p_j + 1});
		}
	}
	return res;
}

function A_star() {
	let open = [];
	var start = {i:points.start.i,j:points.start.j};
	var end = {i:points.end.i,j:points.end.j};

	open.push(board[start.i][start.j]); // color it like open blue circle
	board[start.i][start.j].open = true;
	board[start.i][start.j].d = 0;
	board[start.i][start.j].h = (abs(start.i - end.i) + abs(start.j - end.j)) * 10;

	while (open.length != 0) {
		// find closest open
		var min_el = null;
		var min_dist = 100**100;
		for (var i = 0; i < open.length; i++) {
			if (open[i].open && open[i].d + open[i].h < min_dist) {
				min_el = open[i];
				min_dist = open[i].d + open[i].h;
			}
		}
		// delete it // color it black circle
		var p_i = min_el.i;
		var p_j = min_el.j;
		board[p_i][p_j].open = false;
		board[p_i][p_j].closed = true;
		//if it is end then draw path
		if (p_i == end.i && p_j == end.j) {
			// draw big lines from end to start
			var p = min_el;
			while (p.parent != null) {
				//draw line
				p.main_parent = p.parent;
				p = p.parent;
			}
			return;
		}
		// for every child he have add them to open array // color them in blue circle
		var childs = find_close_cells(p_i, p_j);
		for (var i = 0; i < childs.length; i++) {
			open.push(board[childs[i].i][childs[i].j]);
			board[childs[i].i][childs[i].j].open = true;
			board[childs[i].i][childs[i].j].h = (abs(childs[i].i - end.i) + abs(childs[i].j - end.j)) * 10;
			var new_d = board[p_i][p_j].d;

			if (abs(childs[i].i - p_i) + abs(childs[i].j - p_j) == 2) {
				new_d += 14;
			} else {
				new_d += 10;
			}

			if (board[childs[i].i][childs[i].j].parent == null) {
				board[childs[i].i][childs[i].j].parent = board[p_i][p_j];
				board[childs[i].i][childs[i].j].d = new_d;
			} else {
				if (board[childs[i].i][childs[i].j].d > new_d) {
					board[childs[i].i][childs[i].j].parent = board[p_i][p_j];
				}
			}
		}
		// delayTime(0.5);
	}
}

function keyTyped() {
    if (key === 's') {
        curent_state = 'draw start';
    } else if (key === 'e') {
        curent_state = 'draw end';
    } else if (key === 'b') {
        curent_state = 'draw block';
    } else if (key === 'v') {
        curent_state = 'draw void';
    } else if (key === 'f') {
		if (points.start != null && points.end != null) {
			A_star();
		}
    } else if (key === 'r') {
		for (var i = 0; i < board.length; i++) {
			for (var j = 0; j < board[i].length; j++) {
				board[i][j].parent = null;
				board[i][j].main_parent = null;
				board[i][j].closed = false;
				board[i][j].open = false;
				board[i][j].d = 0;
				board[i][j].h = 0;
			}
		}
    } else if (key === 'p') {
		parse_board();
	} else if (key === 'i') {
		if (index_show == true) {
			index_show = false;
		} else {
			index_show = true;
		}
	}
}

function mouseReleased() {
	var fat = 50;
	var curr = null;
	for (var i = 0; i < board.length; i++) {
		for (var j = 0; j < board[i].length; j++) {
			var a = board[i][j];
			if (a.x < mouseX && mouseX < a.x + fat && a.y < mouseY && mouseY < a.y + fat) {
				curr = {i:i,j:j};
				if (curent_state == 'draw start') {
					if (points.start != null) {
						board[points.start.i][points.start.j].color = void_color;
					}
					board[curr.i][curr.j].color = start_color;
					points.start = curr;
				} else if (curent_state == 'draw end') {
					if (points.end != null) {
						board[points.end.i][points.end.j].color = void_color;
					}
					board[curr.i][curr.j].color = end_color;
					points.end = curr;
				} else if (curent_state == 'draw block') {
					board[curr.i][curr.j].color = block_color;
				} else if (curent_state == 'draw void') {
					board[curr.i][curr.j].color = void_color;
				}
				return;
			}
		}
	}

}

function draw_menu() {
	noStroke();
	textSize(20);
	fill(0, 102, 153);
	text('curr state: ', 50, 30);
	fill(0);
	text(curent_state, 150, 30);

	fill(0, 102, 153);
	text('index show: ', 300, 30);
	fill(0);
	text(index_show, 420, 30);
}

function parse_board() {
	// dont work if f is pressed!!!!
	// need to exicude non 'f' board!!!
	var start_node;
	var end_node;
	var number_of_nodes = 0;
	var number_of_connections = 0;

	var res_conect = [];

	for (var i = 0; i < board.length; i++) {
		for (var j = 0; j < board[i].length; j++) {
			number_of_nodes += 1;
			if (board[i][j].color != block_color) {
				if (board[i][j].color == start_color) {
					start_node = board[i].length * i + j + 1;
				}
				if (board[i][j].color == end_color) {
					end_node = board[i].length * i + j + 1;
				}

				var close = find_close_cells(i, j);

				for (var iter = 0; iter < close.length; iter++) {
					number_of_connections += 1;

					var d;
					if (abs(close[iter].i - i) + abs(close[iter].j - j) == 2) {
						d = 14;
					} else {
						d = 10;
					}
					res_conect.push({from: board[i].length * i + j + 1,
									 to: board[close[iter].i].length * close[iter].i + close[iter].j + 1,
								 	 waight: d});
				}
			}
		}
	}

	let writer = createWriter('newFile.txt');
	// write data to the file
	writer.write(start_node + " " + end_node + "\n");
	writer.write(number_of_nodes + " " + number_of_connections + "\n");
	for (var i = 0; i < res_conect.length; i++) {
		writer.write(res_conect[i].from + " " + res_conect[i].to + " " + res_conect[i].waight + "\n");
	}
	// close the PrintWriter and save the file
	writer.close();
}

function setup_board() {
	var fat = 50;
	for (var i = 50; i < width - 50; i += fat) {
		var a = [];
		for (var j = 50; j < height - 50; j += fat) {
			a.push({x:i, y:j, i:null, j:null,
					color:void_color,
					open:false, closed:false,
					parent:null, main_parent:null,
					d:0, h:0});
		}
		board.push(a);
	}

	for (var i = 0; i < board.length; i++) {
		for (var j = 0; j < board[i].length; j++) {
			board[i][j].i = i;
			board[i][j].j = j;
		}
	}
}

function draw_board() {
	var fat = 50;
	for (var i = 0; i < board.length; i++) {
		for (var j = 0; j < board[i].length; j++) {
			var a = board[i][j];
			stroke(border_color);
			strokeWeight(2);
			fill(a.color);
			rect(a.x, a.y, fat, fat, 10);
			if (a.open == true) {
				stroke(open_cell_color);
				strokeWeight(4);
				noFill();
				ellipse(a.x + 25, a.y + 25, 20);
			}
			if (a.closed == true) {
				stroke(closed_cell_color);
				strokeWeight(4);
				noFill();
				ellipse(a.x + 25, a.y + 25, 20);
			}
			if (a.d != 0) {
				noStroke();
				textSize(10);
				fill(0);
				text(a.d, a.x + 4, a.y + 40);
			}
			if (a.h != 0) {
				noStroke();
				textSize(10);
				fill(0);
				text(a.h, a.x + 36, a.y + 40);
			}
			if (index_show == true) {
				noStroke();
				textSize(10);
				fill(0);
				text(board[i].length * i + j + 1, a.x + 5, a.y + 10);
			}
		}
	}

	for (var i = 0; i < board.length; i++) {
		for (var j = 0; j < board[i].length; j++) {
			var a = board[i][j];
			if (a.parent != null) {
				stroke(closed_cell_color);
				strokeWeight(1);
				noFill();
				line(a.parent.x + 25, a.parent.y + 25, a.x + 25, a.y + 25);
			}
			if (a.main_parent != null) {
				stroke(main_parent_color);
				strokeWeight(4);
				noFill();
				line(a.parent.x + 25, a.parent.y + 25, a.x + 25, a.y + 25);
			}
		}
	}
}

function setup() {
	createCanvas(800, 400);
	background(background_color);
	setup_board();
}

function draw() {
	background(background_color);
	draw_board();
	draw_menu();
}
