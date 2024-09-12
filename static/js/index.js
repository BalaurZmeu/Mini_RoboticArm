console.log('JavaScript file loaded');

function getCSRFToken() {
  return document.querySelector('input[name="csrfmiddlewaretoken"]').value;
}

function sendCommand(action) {
  const xhr = new XMLHttpRequest();
  xhr.open('POST', '/robot/', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.setRequestHeader('X-CSRFToken', getCSRFToken());  // Fetch CSRF token correctly

  xhr.onreadystatechange = function() {
    if (xhr.readyState === XMLHttpRequest.DONE) {
      console.log('Command sent:', action);
      if (xhr.status === 200) {
        console.log('Success:', xhr.responseText);
      } else {
        console.log('Error:', xhr.status, xhr.responseText);
      }
    }
  };

  xhr.send('action=' + action);
}

