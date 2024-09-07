from django.urls import path
from . import views


urlpatterns = [
    path(
        '',
        views.index,
        name='index'),
    
    path(
        'robot/',
        views.control_robotic_arm,
        name='robot'),
]    

