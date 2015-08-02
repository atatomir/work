var fin,fout:text;
    cod:string;
    i: integer;
    dcod:char;


begin

assign(fin,'fin.bin'); reset(fin);
assign(fout,'fout.bin'); rewrite(fout);
read(fin,cod);
 for i := 1 to length(cod) do
 begin
 dcod := pred(cod[i]);
 write(fout,dcod);
 end;



close(fout);
close(fin);
end.