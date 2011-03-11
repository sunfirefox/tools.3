;
; install.iss -- Inno Setup 4 install configuration file
;
; Copyright (c) Embedthis Software LLC, 2003-2011. All Rights Reserved.
;

[Setup]
AppName=!!BLD_NAME!!
AppVerName=!!BLD_NAME!! !!BLD_VERSION!!-!!BLD_NUMBER!!
DefaultDirName={sd}!!BLD_PREFIX!!
DefaultGroupName=!!BLD_NAME!!
UninstallDisplayIcon={app}\!!BLD_PRODUCT!!.exe
LicenseFile=LICENSE.TXT

[Icons]
Name: "{group}\ReadMe"; Filename: "{app}\README.TXT"

[Types]
Name: "full"; Description: "Complete Installation with Documentation and Samples"; 
Name: "binary"; Description: "Binary Installation"; 
Name: "documentation"; Description: "Documentation and Samples Installation"; 
Name: "development"; Description: "Development Haders and Samples Installaion"; 

[Components]
Name: "bin"; Description: "Binary Files"; Types: binary full;
Name: "doc"; Description: "Documentation Files"; Types: documentation full;
Name: "dev"; Description: "Developmente Headers and Samples"; Types: development full;

[Dirs]

[UninstallDelete]

[Code]
function IsPresent(const file: String): Boolean;
begin
  if FileExists(file) then begin
    Result := True;
  end else begin
    Result := False;
  end
end;

[Run]
Filename: "{app}\doc\product\index.html"; Description: "View the Documentation"; Flags: skipifsilent waituntilidle shellexec postinstall; Check: IsPresent('{app}\doc\product\index.html'); Components: bin

[UninstallRun]
Filename: "{app}\remove.exe"; Parameters: "-r -s 5"; WorkingDir: "{app}"; Flags:

[Files]
