import os
import ycm_core


flags = '-std=c++11 -stdlib=libc++ -fPIC -pthread -I/home/teto/ns3off/build -DNS3_ASSERT_ENABLE -DNS3_LOG_ENABLE -DHAVE_SYS_IOCTL_H=1 -DHAVE_IF_NETS_H=1 -DHAVE_NET_ETHERNET_H=1 -DHAVE_PACKET_H=1 -DHAVE_IF_TUN_H=1 c++ -isystem /usr/include/c++/4.9'.split()
#return  {
    #'flags': flags,
    #'do_cache': True
    #}

compilation_database_folder = '/home/teto/ns3off/build'

print("hello world")


if os.path.exists( compilation_database_folder ):
  database = ycm_core.CompilationDatabase( compilation_database_folder )
else:
  database = None

SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', '.m', '.mm' ]

def DirectoryOfThisScript():
  return os.path.dirname( os.path.abspath( __file__ ) )


def MakeRelativePathsInFlagsAbsolute( flags, working_directory ):
  if not working_directory:
    return list( flags )
  new_flags = []
  make_next_absolute = False
  path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
  for flag in flags:
    new_flag = flag

    if make_next_absolute:
      make_next_absolute = False
      if not flag.startswith( '/' ):
        new_flag = os.path.join( working_directory, flag )

    for path_flag in path_flags:
      if flag == path_flag:
        make_next_absolute = True
        break

      if flag.startswith( path_flag ):
        path = flag[ len( path_flag ): ]
        new_flag = path_flag + os.path.join( working_directory, path )
        break

    if new_flag:
      new_flags.append( new_flag )
  return new_flags


def IsHeaderFile( filename ):
  extension = os.path.splitext( filename )[ 1 ]
  return extension in [ '.h', '.hxx', '.hpp', '.hh' ]


def GetCompilationInfoForFile( filename ):
  # The compilation_commands.json file generated by CMake does not have entries
  # for header files. So we do our best by asking the db for flags for a
  # corresponding source file, if any. If one exists, the flags for that file
  # should be good enough.
  if IsHeaderFile( filename ):
    basename = os.path.splitext( filename )[ 0 ]
    for extension in SOURCE_EXTENSIONS:
      replacement_file = basename + extension
      if os.path.exists( replacement_file ):
        compilation_info = database.GetCompilationInfoForFile(
          replacement_file )
        if compilation_info.compiler_flags_:
          return compilation_info
    return None
  return database.GetCompilationInfoForFile( filename )


def FlagsForFile( filename, **kwargs ):

  print("hello world")

  #if database:
    ## Bear in mind that compilation_info.compiler_flags_ does NOT return a
    ## python list, but a "list-like" StringVec object
    #compilation_info = GetCompilationInfoForFile( filename )
    #if not compilation_info:
      #return None

    #final_flags = MakeRelativePathsInFlagsAbsolute(
      #compilation_info.compiler_flags_,
      #compilation_info.compiler_working_dir_ )

    ## NOTE: This is just for YouCompleteMe; it's highly likely that your project
    ## does NOT need to remove the stdlib flag. DO NOT USE THIS IN YOUR
    ## ycm_extra_conf IF YOU'RE NOT 100% SURE YOU NEED IT.
    ##try:
      ##final_flags.remove( '-stdlib=libc++' )
    ##except ValueError:
      ##pass
  #else:
    #relative_to = DirectoryOfThisScript()
    #final_flags = MakeRelativePathsInFlagsAbsolute( flags, relative_to )

  return {
    #'flags': final_flags,
    'flags': flags,
    'do_cache': True
  }
