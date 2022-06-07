extends Camera2D


onready var topLeft = $Limits/TopLeft
onready var bottomRight = $Limits/BottomRight
#camera is limited using position nodes
func _ready():
	limit_top = topLeft.position.y
	limit_left = topLeft.position.x
	limit_bottom = bottomRight.position.y
	limit_right = bottomRight.position.x
