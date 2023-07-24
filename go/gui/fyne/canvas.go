package main

import (
	"image/color"
	//"time"

	"fyne.io/fyne/v2"
	"fyne.io/fyne/v2/app"
	"fyne.io/fyne/v2/canvas"
	"fyne.io/fyne/v2/container"
)

func main() {
	myApp := app.New()
	myWindow := myApp.NewWindow("Canvas")
	myCanvas := myWindow.Canvas()

	blue := color.NRGBA{R: 0, G: 0, B: 180, A: 255}
	//rect := canvas.NewRectangle(blue)
	//myCanvas.SetContent(rect)

	black := color.NRGBA{R:0, G:0, B:0, A:255}
	xline := canvas.NewLine(black)
	yline := canvas.NewLine(blue)
	o := canvas.NewText("o", black)
	o.Move(fyne.Position{X:300,Y:300})
	xline.Position1 = fyne.Position{X:100,Y:300}
	xline.Position2 = fyne.Position{X:500,Y:300}
	yline.Position1 = fyne.Position{X:300,Y:100}
	yline.Position2 = fyne.Position{X:300,Y:500}
	xline.Hidden = false
	yline.Hidden = false
	o.Hidden = false
	content := container.NewWithoutLayout(xline, yline, o)
	myCanvas.SetContent(content)
	//myCanvas.SetContent(yline)


	/*var red uint8 = 0
	go func() {
		for {
		time.Sleep(time.Second)
		red = (red + 50) % 255
		green := color.NRGBA{R: red, G: 180, B: red, A: 255}
		rect.FillColor = green
		rect.Refresh()
		} 
	}()*/

	myWindow.Resize(fyne.NewSize(700, 700))
	myWindow.ShowAndRun()
}
