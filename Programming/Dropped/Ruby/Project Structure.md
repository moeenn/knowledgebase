```
src/
	main.rb
test/
Gemfile
Rakefile
```

```Gemfile
source 'https://rubygems.org'
gem 'minitest'
gem 'rake'
gem 'rubocop'
```

```rb
# file: Rakefile
require 'rubocop/rake_task'

task default: %w[lint test]

RuboCop::RakeTask.new(:lint) do |task|
   task.patterns = ['lib/**/*.rb', 'test/**/*.rb']
   task.fail_on_error = false
end

task :run do
  ruby 'src/main.rb'
end

task :test do
  ruby 'test/main.rb'
end
```

```rb
# file: main.rb
puts "Hello world"
```


#### Running the project

```bash
$ rake run
```