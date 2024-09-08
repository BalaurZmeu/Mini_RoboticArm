// JavaScript function to send AJAX requests for controlling the robotic arm
function sendCommand(action) {
  const xhr = new XMLHttpRequest();
  xhr.open('POST', '/robot/', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  // Ensure CSRF token is sent in Django
  xhr.setRequestHeader('X-CSRFToken', '{{ csrf_token }}');

  xhr.onreadystatechange = function() {
    if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
      console.log('Command sent:', action);
    }
  };

  xhr.send('action=' + action);
}

