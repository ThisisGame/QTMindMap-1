RMDIR OpenCppCoverage /s /q
OpenCppCoverage.exe --sources MindMap --excluded_sources MindMapTest --output OpenCppCoverage -- Binary\MindMapTest.exe
start OpenCppCoverage\index.html