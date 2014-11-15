RMDIR OpenCppCoverage /s /q
OpenCppCoverage.exe --sources MindMap --excluded_sources MindMapTest --output OpenCppCoverage -- x64\Debug\MindMapTest.exe
start OpenCppCoverage\index.html