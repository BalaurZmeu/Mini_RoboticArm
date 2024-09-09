import serial
from django.shortcuts import render
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt

def index(request):
    return render(request, 'index.html')

@csrf_exempt
def control_robotic_arm(request):
    if request.method == 'POST':
        action = request.POST.get('action')
        if action:
            # Connect to Arduino over serial and send the action
            with serial.Serial('/dev/ttyUSB0', 9600, timeout=1) as ser:
                ser.write(action.encode())  # Send action as bytes

            # Return success response
            return JsonResponse({'status': 'success', 'action': action})

    # Return error response if the action is invalid or method is not POST
    return JsonResponse({'status': 'error', 'message': 'Invalid request'}, status=400)

