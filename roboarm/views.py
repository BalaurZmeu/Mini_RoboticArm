import requests
from django.shortcuts import render
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt


# IP address of the ESP8266 board
ESP8266_IP = 'http://192.168.0.102'


def index(request):
    return render(request, 'index.html')


@csrf_exempt
def control_robotic_arm(request):
    if request.method == 'POST':
        action = request.POST.get('action')
        
        if action:
            try:
                # Send the command to the ESP8266 through its server
                response = requests.get(
                    f'{ESP8266_IP}/control',
                    params={'action': action},
                )
                
                # Check if the response from ESP8266 is OK
                if response.status_code == 200:
                    return JsonResponse(
                        {
                            'status': 'success',
                            'message': response.text,
                        }
                    )
                else:
                    return JsonResponse(
                        {
                            'status': 'error',
                            'message': 'ESP8266 returned an error',
                        },
                        status=500,
                    )
            
            except requests.RequestException as e:
                return JsonResponse(
                    {
                        'status': 'error',
                        'message': str(e)
                    },
                    status=500,
                )

    return JsonResponse(
        {
            'status': 'error',
            'message': 'Invalid request',
        },
        status=400,
    )

