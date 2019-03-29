<template>
  <el-tabs :tab-position="tabpos" style="" lazy>
    <el-tab-pane label="记录管理">
      <line-manager v-if="show"></line-manager>
    </el-tab-pane>
    <el-tab-pane label="新增记录" lazy>
      <el-card>
        <el-form ref="form" :model="form" label-width="100px" >
          <el-form-item label="车次" required prop="number">
            <el-input v-model="form.number"></el-input>
          </el-form-item>
          <el-form-item label="商务座数量" required prop="businessClass">
            <el-input v-model="form.businessClass"></el-input>
          </el-form-item>
          <el-form-item label="一等座数量" required prop="firstClass">
            <el-input v-model="form.firstClass"></el-input>
          </el-form-item>
          <el-form-item label="二等座数量" required prop="secondClass">
            <el-input v-model="form.secondClass"></el-input>
          </el-form-item>
          <el-form-item prop="stations" v-for="(station, index) in form.stations" :label="'途经第' + (index + 1) + '站:'" :key="index" required>
            <el-input v-model="station.name"></el-input>
            <el-input class="time" placeholder="区间价格" v-model="station.price"></el-input>
            <el-time-select class="time" placeholder="出发时间" v-model="station.time" :picker-options="{start: '05:30',step: '00:01',end: '23:59'}"></el-time-select>
            <el-button size="small" type="danger" @click.prevent="removeStation(station)">删除</el-button>
          </el-form-item>
          <div class="btn2">
            <el-button class="btn2" type="success" @click="addStation">新增站点</el-button>
          </div>
          <div class="bottom clearfix">
            <el-button class="btn" @click="resetForm('form')">重置</el-button>
            <el-button class="btn" type="primary" @click="submit">提交</el-button>
          </div>
        </el-form>              
      </el-card>
    </el-tab-pane> 
  </el-tabs>
</template>

<script>
  import LineManager from './Controls/LineManager.vue'
  let fs = require('fs')
  export default {
    name: 'admin-page',
    components: {
      LineManager
    },
    methods: {
      submit () {
        console.log(this.form)
        // let dat = this.form.number + ' ' + this.form.businessClass + ' ' + this.form.firstClass + ' ' + this.form.secondClass + ' ' + this.form.stations.length
        // for (let x in this.form.stations) {
        //  dat += ' ' + this.form.stations[x].name + ' ' + this.form.stations[x].time + ' ' + this.form.stations[x].price
        // }
        fs.readFile(this.path + '/lines.json', (err, data) => {
          if (!err) {
            let lines = JSON.parse(data) // 读取
            lines.push(this.form) // 追加
            fs.writeFile(this.path + '/lines.json', JSON.stringify(lines), (err) => {
              if (!err) {
                this.$message({message: '添加成功!', type: 'success', showClose: true})
                this.refresh()
              } else {
                this.$message({message: err, type: 'warning', showClose: true})
              }
            })
          } else {
            let arr = [this.form] // 直接
            fs.writeFile(this.path + '/lines.json', JSON.stringify(arr), (err) => {
              if (!err) {
                this.$message({message: '添加成功!', type: 'success', showClose: true})
                this.refresh()
              } else {
                this.$message({message: err, type: 'warning', showClose: true})
              }
            })
          }
        })
      },
      resetForm (formName) {
        this.$refs[formName].resetFields()
      },
      removeStation (item) {
        var index = this.form.stations.indexOf(item)
        if (index !== -1) {
          this.form.stations.splice(index, 1)
        }
      },
      addStation () {
        this.form.stations.push({
          name: '',
          price: '',
          time: ''
        })
      },
      refresh () {
        console.log(0)
        this.show = false
        this.$nextTick(() => (this.show = true)) // 刷新组件
      }
    },
    created () {
      const { ipcRenderer } = require('electron')
      ipcRenderer.send('get-app-path')
      ipcRenderer.on('got-app-path', (event, path) => {
        this.path = path
      })
      this.addStation()
    },
    data () {
      return {
        path: '',
        show: true,
        tabpos: 'left',
        form: {
          number: '',
          businessClass: 100,
          firstClass: 100,
          secondClass: 100,
          stations: [{name: '', price: '0', time: ''}]
        }
      }
    }
  }
</script>

<style>
  .btn {
    float: right;
    margin: 0.5rem;
  }
  .btn2 {
    text-align: center;
    margin: 0.5rem
  }
  .time {
      margin-top: 0.3rem;
  }
</style>
