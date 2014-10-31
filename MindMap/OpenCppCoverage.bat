RMDIR OpenCppCoverage /s /q
OpenCppCoverage.exe --sources MindMap --output OpenCppCoverage -- Binary\MindMapTest.exe
start OpenCppCoverage\index.html