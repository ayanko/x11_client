require "bundler/gem_tasks"
require 'rake/extensiontask'

Rake::ExtensionTask.new('x11_client_ext')

desc "Update lib/x11_client/keysym.rb"
task :update_keysym, [:source_dir] do |task, args|
  source_dir = args[:source_dir] || "/usr/include/X11"
  target = "lib/x11_client/keysym.rb"

  source_files = Dir[File.join(source_dir, '*sym*.h')]
  abort("No keysym files found") if source_files.empty?

  puts "Updating #{target} from #{source_dir} directory"

  File.open(target, "w") do |target_file|

    target_file << "class X11Client\n"
    target_file << "  KEYSYM = {\n"

    source_files.each do |source_file|
      puts "Processing #{source_file}"

      target_file << "\n"
      target_file << "    # #{source_file}\n"
      File.open(source_file).each_line do |line|
        if line =~ /^#define[\s\t]+([\w_]+)[\s\t]+(0x[0-9a-f]+)/
          target_file << "    %-40s => %s,\n" % ["'#{$1}'", $2]
        end
      end
    end

    target_file << "  }\n"
    target_file << "end\n"
  end
end
