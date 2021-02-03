{
	"folders": [],
	"launch": {
		"version": "0.2.0",
		"configurations": [
			{
				"name": "gcc-5 - 활성 파일 빌드 및 디버그",
				"type": "cppdbg",
				"request": "launch",
				"program": "${fileDirname}/${fileBasenameNoExtension}",
				"args": [],
				"stopAtEntry": false,
				"cwd": "${workspaceFolder}",
				"environment": [],
				"console": "externalTerminal",
				"MIMode": "gdb",
				"setupCommands": [
					{
						"description": "gdb에 자동 서식 지정 사용",
						"text": "-enable-pretty-printing",
						"ignoreFailures": true
					}
				],
				"preLaunchTask": "C/C++: gcc-5 활성 파일 빌드",
				"miDebuggerPath": "/usr/bin/gdb"
			}
		]
	}
}