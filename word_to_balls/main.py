import sys
import arcade
import numpy as np
import matplotlib.pyplot as plt
from PIL import ImageOps

# First parse CLA
assert len(sys.argv) > 3
FULL_WIDTH = int(sys.argv[1])
FULL_HEIGHT = int(sys.argv[2])
TEXT   = ''
for word in sys.argv[3:-1]:
    TEXT += word + '\n'
TEXT += sys.argv[-1]

SCALE  = 5
HEIGHT = FULL_HEIGHT // SCALE
WIDTH  = FULL_WIDTH // SCALE
FPS    = 60

# Grayscale image as array
img_arr = None

def on_draw(delta_time):
    global img_arr
    arcade.start_render()
    arcade.draw_text(
        TEXT, 
        WIDTH//2, 
        HEIGHT//2, 
        arcade.color.WHITE, 
        10 * 18 // SCALE, 
        align="center",
        anchor_x="center", 
        anchor_y="center")
    
    image = arcade.get_image()
    image = ImageOps.grayscale(image)
    img_arr = np.array(image)
    img_arr = np.flip(img_arr, axis=0)
    arcade.close_window()

# Setup rendering/drawing
arcade.open_window(WIDTH, HEIGHT, '')
arcade.set_background_color(arcade.color.BLACK)

# Tell the computer to call the draw command at the specified interval.
arcade.schedule(on_draw, 1 / FPS)

# Run the program
arcade.run()


# Write this final array as a file
ball_data = open('word_to_balls/word_as_balls', 'w')

# upsample by SCALE
rows, cols = img_arr.shape
new_img = np.zeros((SCALE * rows, SCALE * cols))
for r in range(SCALE * rows):
    for c in range(SCALE * cols):
        if r % SCALE == 0 and c % SCALE == 0:
            new_img[r, c] = 1 if img_arr[r//SCALE, c//SCALE] > 100 else 0     
        ball_data.write(str(int(new_img[r,c])))
        ball_data.write(' ') 
    ball_data.write('\n')   
ball_data.close()

# plt.imshow(new_img, cmap='gray')
# plt.show()