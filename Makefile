
.PHONY: clean webgpu-native

webgpu-native:
	mkdir -p build/webgpu-native
	python scripts/generate.py -t templates/webgpu.template.hpp -o build/webgpu-native/ -u todo/wgpu-native/webgpu.h -u todo/wgpu-native/wgpu.h

clean:
	rm -rf build/