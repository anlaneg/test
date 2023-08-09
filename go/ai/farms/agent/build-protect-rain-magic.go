package agent

import (
	"github.com/anlaneg/frame/frame"
	//"fmt"
)

/*这个agent只建造自已的保护区，同时在cd时间内总对自已的保护区下雨*/
type BuildProtectRainMaigcAgent struct {
	frame.Agent
	index int
}

func (protect *BuildProtectRainMaigcAgent) Init() {
	protect.index = 0
}

func (protect *BuildProtectRainMaigcAgent) GetRequest() *frame.Request {
	if(protect.index >= frame.GAMEMAP_MAX_PROTECT_COLUMNS * frame.GAMEMAP_MAX_ROWS) {
		return nil
	}
	
	row := protect.index % frame.GAMEMAP_MAX_ROWS
	column := protect.index / frame.GAMEMAP_MAX_ROWS
	protect.index ++
	
	return &frame.Request{Name:frame.PlaceType_garden,Row:row,Column:column}
}

func (protect *BuildProtectRainMaigcAgent) GetMagic() interface{} {
	/*rain for protect area*/
	return &frame.Rain{Column:1}
}
