ffmpeg -r 10 -i lattice%%06d.png -c:v libx264 -r 30 -pix_fmt yuv420p AVideo.mp4