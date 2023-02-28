import sys

class_name = sys.argv[1];
print(class_name.lower());

# Create .gdns file
GDNSFile = open('../demo/bin/' + class_name.lower() + '.gdns', 'w')
GDNSFile.write(
    '[gd_resource type="NativeScript" load_steps=2 format=2]\n' + 
    '[ext_resource path="res://bin/gdexample.gdnlib" type="GDNativeLibrary" id=1]\n'
    '[resource]\n' +
    'resource_name = "' + class_name.lower() + '"\n' +
    'class_name = "' + class_name + '"\n' +
    'library = ExtResource( 1 )');
GDNSFile.close();

# Create .h files
HFile = open('../src/' + class_name.lower() + '.h', 'w')
with open('HTEMPLATE.txt', 'r') as file:
    data = file.read().replace('CLASS_NAME', class_name)
    HFile.write(data);
    HFile.close();

# Create .cpp files
CPPFile = open('../src/' + class_name.lower() + '.cpp', 'w')
with open('CPPTEMPLATE.txt', 'r') as file:
    data = file.read().replace('CLASS_NAME', class_name).replace('class_name_lower', class_name.lower());
    CPPFile.write(data);
    CPPFile.close();

# Old method
# fp = open('../src' + class_name.lower() + '.h', 'x')
# fp.write('#include <Godot.hpp>\n'+
#     'namespace godot {\n\n'+
#     'class CLASS_NAME : public Node {\n'+
#     '   GODOT_CLASS(Player, Node)\n\n'+
#     'private:\n\n'+
#     'public:\n'+
#     'static void _register_methods();\n\n'+
#     'CLASS_NAME();\n'+
#     '~CLASS_NAME();\n\n'+
#     'void _init();\n'+
#     'void _process(float delta);\n'
# '};}');
# fp.close();