var ws;
var is_button_down = false;

window.addEventListener("DOMContentLoaded", event => {
    document.getElementById("left_rotate").onclick = function() {rotate_left()};
    document.getElementById("left_shift").onclick = function() {shift_left()};
    document.getElementById("right_rotate").onclick = function() {rotate_right()};
    document.getElementById("right_shift").onclick = function() {shift_right()};
    document.getElementById("move_forward").onclick = function() {move_forward()};
    document.getElementById("move_backward").onclick = function() {move_backward()};

    document.getElementById("left_rotate").onmouseup = function() {stop()};
    document.getElementById("left_shift").onmouseup = function() {stop()};
    document.getElementById("right_rotate").onmouseup = function() {stop()};
    document.getElementById("right_shift").onmouseup = function() {stop()};
    document.getElementById("move_forward").onmouseup = function() {stop()};
    document.getElementById("move_backward").onmouseup = function() {stop()};

    ws = create_web_socket();
})

function rotate_left() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('rotate_left');
    }
    is_button_down = true;
}

function shift_left() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('shift_left');
    }
    is_button_down = true;
}

function rotate_right() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('rotate_right');
    }
    is_button_down = true;
}

function shift_right() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('shift_right');
    }
    is_button_down = true;
}

function move_forward() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('move_forward');
    }
    is_button_down = true;
}

function move_backward() {
    open_socket_if_closed();
    if (!is_button_down) {
        ws.send('move_backward');
    }
    is_button_down = true;
}

function stop() {
    open_socket_if_closed();
    ws.send('stop');
    is_button_down = false;
}

function create_web_socket() {
    car_ip = document.getElementById('car_ip_save').textContent.trim();
    return new WebSocket('ws://' + car_ip + ':80/ws');
}

function open_socket_if_closed() {
    if(!(ws.readyState === ws.OPEN)) {
        create_web_socket();
    }
}

window.addEventListener("keydown", function (event) {
    if (event.defaultPrevented) {
      return; // Do nothing if the event was already processed
    }
  
    switch (event.key) {
        case "q":
            rotate_left();
            break;
        case "w":
            move_forward();
            break;
        case "e":
            rotate_right();
            break;
        case "a":
            shift_left();
            break;
        case "s":
            move_backward();
            break;
        case "d":
            shift_right();
            break;
      default:
        return; // Quit when this doesn't handle the key event.
    }
  
    // Cancel the default action to avoid it being handled twice
    event.preventDefault();
  }, true);

  window.addEventListener("keyup", function (event) {
    if (event.defaultPrevented) {
      return; // Do nothing if the event was already processed
    }
  
    switch (event.key) {
        case "q":
            stop();
            break;
        case "w":
            stop();
            break;
        case "e":
            stop();
            break;
        case "a":
            stop();
            break;
        case "s":
            stop();
            break;
        case "d":
            stop();
            break;
      default:
        return; // Quit when this doesn't handle the key event.
    }
  
    // Cancel the default action to avoid it being handled twice
    event.preventDefault();
  }, true);
