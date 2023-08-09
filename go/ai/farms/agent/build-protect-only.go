package agent

import (
	"github.com/anlaneg/frame/frame"
	//"fmt"
)

/*这个agent只建造自已的保护区*/
type BuildProtectOnlyAgent struct {
	frame.Agent
	index int
}

func (protect *BuildProtectOnlyAgent) Init() {
	protect.index = 0
}

func (protect *BuildProtectOnlyAgent) GetRequest() *frame.Request {
	if(protect.index >= frame.GAMEMAP_MAX_PROTECT_COLUMNS * frame.GAMEMAP_MAX_ROWS) {
		return nil
	}
	
	row := protect.index % frame.GAMEMAP_MAX_ROWS
	column := protect.index / frame.GAMEMAP_MAX_ROWS
	protect.index ++
	
	//fmt.Printf("%s build %s at [%2d,%2d]\n", protect.name, frame.PlaceType_garden, row, column)
	return &frame.Request{Name:frame.PlaceType_garden,Row:row,Column:column}
}

func (protect *BuildProtectOnlyAgent) GetMagic() interface{} {
	return nil
}
