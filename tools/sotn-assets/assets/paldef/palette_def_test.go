package paldef

import (
	"bytes"
	"encoding/binary"
	"testing"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestNoncontiguousDefinitions(t *testing.T) {
	const base psx.Addr = 0x80180000
	data := bytes.Repeat([]byte{0xA4}, 0x180)
	put := func(offset int, words ...uint32) {
		for i, word := range words {
			binary.LittleEndian.PutUint32(data[offset+i*4:], word)
		}
	}
	put(0x40, 5, 0x2000, 16, uint32(base+0x80), 0xFFFFFFFF)
	put(0xA0, 0x20004, 0x2200, 2, uint32(base+0x100), uint32(base+0x120), 0xFFFFFFFF)
	put(0x160, uint32(base+0xA0), uint32(base+0x40), uint32(base+0xA0))
	r := bytes.NewReader(data)
	pointers, err := readClutsPointers(r, base, 0x160, 0x16C)
	if err != nil {
		t.Fatal(err)
	}
	defs, err := readPaletteDefsAt(r, base, pointers)
	if err != nil {
		t.Fatal(err)
	}
	if len(defs) != 2 || defs[1].Kind != 4 || defs[1].Freq != 2 || len(defs[1].Data) != 2 || defs[0].Entries[0].Length != 16 {
		t.Fatalf("wrong palette definitions: %+v", defs)
	}
	cluts, err := readClutsArray(r, base, 0x160, 0x16C, defs)
	if err != nil {
		t.Fatal(err)
	}
	if len(cluts) != 3 || cluts[0] != 1 || cluts[1] != 0 || cluts[2] != 1 {
		t.Fatalf("cluts order or duplicate lost: %v", cluts)
	}
	put(0xA0, 0xA4000000)
	if _, err := readPaletteDefsAt(bytes.NewReader(data), base, pointers); err == nil {
		t.Fatal("invalid palette opcode accepted")
	}
	if _, err := readPaletteDefsAt(bytes.NewReader(data[:0x44]), base, []psx.Addr{base + 0x40}); err == nil {
		t.Fatal("truncated definition accepted")
	}
}
