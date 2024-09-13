console.log('JavaScript file loaded');

/*****************************************************************************/

// Function to GET csrftoken from Cookie
function getCookie(name) {
    var cookieValue = null;
    if (document.cookie && document.cookie !== '') {
        var cookies = document.cookie.split(';');
        for (var i = 0; i < cookies.length; i++) {
            var cookie = cookies[i].trim();  // Use native JavaScript trim
            // Does this cookie string begin with the name we want?
            if (cookie.substring(0, name.length + 1) === (name + '=')) {
                cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                break;
            }
        }
    }
    return cookieValue;
}

var csrftoken = getCookie('csrftoken');

/*****************************************************************************/

function csrfSafeMethod(method) {
    // these HTTP methods do not require CSRF protection
    return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

/*****************************************************************************/

function sendCommand(action) {
  const xhr = new XMLHttpRequest();
  xhr.open('POST', '/robot/', true);
  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
  xhr.setRequestHeader('X-CSRFToken', csrftoken);  // Fetch CSRF token correctly

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

