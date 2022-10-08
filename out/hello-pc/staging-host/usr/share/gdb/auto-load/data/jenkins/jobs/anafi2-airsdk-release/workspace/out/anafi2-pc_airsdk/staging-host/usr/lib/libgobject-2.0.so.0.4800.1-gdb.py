import sys
import gdb

# Update module path.
dir_ = '/data/jenkins/jobs/anafi2-airsdk-release/workspace/out/anafi2-pc_airsdk/staging-host/usr/share/glib-2.0/gdb'
if not dir_ in sys.path:
    sys.path.insert(0, dir_)

from gobject import register
register (gdb.current_objfile ())
